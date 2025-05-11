#include "model/Calendar.h"
#include <string>

namespace model {

Calendar::Calendar() = default;

Calendar::~Calendar() {
    if (calendar_) {
        icalcomponent_free(calendar_);
    }
}

void Calendar::setData(const std::vector<uint8_t>& rawData) {
    // Liberar si había un calendario previo
    if (calendar_) {
        icalcomponent_free(calendar_);
        calendar_ = nullptr;
    }
    // Parsear el string .ics
    icalparser* parser = icalparser_new();
    std::string s(rawData.begin(), rawData.end());
    calendar_ = icalparser_parse_string(parser, s.c_str());
    icalparser_free(parser);
}

std::vector<Calendar::Period> Calendar::findPeriods(const TimePoint& when) const {
    std::vector<Period> out;
    if (!calendar_) return out;

    // Convertimos el instante a libical
    icaltimetype target = timePointToIcal(when);

    // Iteramos cada VEVENT
    for (auto comp = icalcomponent_get_first_component(calendar_, ICAL_VEVENT_COMPONENT);
         comp;
         comp = icalcomponent_get_next_component(calendar_, ICAL_VEVENT_COMPONENT))
    {
        // DTSTART
        auto p_dtstart = icalcomponent_get_first_property(comp, ICAL_DTSTART_PROPERTY);
        if (!p_dtstart) continue;
        icaltimetype dtstart = icalproperty_get_dtstart(p_dtstart);

        // DTEND o DURATION
        icaltimetype dtend = dtstart;
        if (auto p_dtend = icalcomponent_get_first_property(comp, ICAL_DTEND_PROPERTY)) {
            dtend = icalproperty_get_dtend(p_dtend);
        } else if (auto p_dur = icalcomponent_get_first_property(comp, ICAL_DURATION_PROPERTY)) {
            auto dur = icalproperty_get_duration(p_dur);
            dtend = icaltime_add(dtstart, dur);
        }
        auto durSeconds = durationBetween(dtstart, dtend);

        // ¿Tiene RRULE?
        if (auto p_rrule = icalcomponent_get_first_property(comp, ICAL_RRULE_PROPERTY)) {
            auto recur = icalproperty_get_rrule(p_rrule);
            auto it = icalrecur_iterator_new(recur, dtstart);
            icaltimetype next;
            while ((next = icalrecur_iterator_next(it)).is_valid) {
                if (icaltime_compare(next, target) == 0) {
                    // coincidencia exacta
                    TimePoint st = when;
                    TimePoint ed = when + durSeconds;
                    out.emplace_back(st, ed);
                }
            }
            icalrecur_iterator_free(it);
        } else {
            // evento simple: si el instante cae dentro [dtstart, dtend)
            if (icaltime_compare(target, dtstart) >= 0 &&
                icaltime_compare(target, dtend) <  0)
            {
                out.emplace_back(icalToTimePoint(dtstart),
                                 icalToTimePoint(dtend));
            }
        }
    }
    return out;
}

bool Calendar::checkMoment(const TimePoint& when) const {
    return !findPeriods(when).empty();
}

// --- Helpers ---

Calendar::TimePoint Calendar::icalToTimePoint(const icaltimetype& tt) {
    time_t t = icaltime_as_timet(tt);
    return std::chrono::system_clock::from_time_t(t);
}

icaltimetype Calendar::timePointToIcal(const TimePoint& tp) {
    time_t t = std::chrono::system_clock::to_time_t(tp);
    auto tt = icaltime_from_timet(t, /* UTC */ true);
    tt.is_date = 0;
    return tt;
}

std::chrono::seconds Calendar::durationBetween(const icaltimetype& start,
                                               const icaltimetype& end)
{
    time_t ts = icaltime_as_timet(start);
    time_t te = icaltime_as_timet(end);
    return std::chrono::seconds(te - ts);
}

} // namespace model
