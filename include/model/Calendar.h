#pragma once

#include "model/ExtendedModel.h"
#include <vector>
#include <chrono>
#include <cstdint>
#include <libical/ical.h>

namespace model {

/// Calendario con soporte de RRULE idéntico al de ical4j
class Calendar : public ExtendedModel {
public:
    using TimePoint = std::chrono::system_clock::time_point;
    /// Un período desde start hasta end
    using Period = std::pair<TimePoint, TimePoint>;

    Calendar();
    ~Calendar();

    /// Carga datos iCalendar crudos (todos los VEVENT, RRULE, RDATE, EXDATE…)
    /// @param rawData bytes del .ics
    void setData(const std::vector<uint8_t>& rawData);

    /// Devuelve todos los periodos que ocurren *exactamente* en el instante `when`
    std::vector<Period> findPeriods(const TimePoint& when) const;

    /// True si existe al menos un VEVENT (o recurrencia) en ese instante
    bool checkMoment(const TimePoint& when) const;

private:
    icalcomponent* calendar_{nullptr};

    // Helpers de conversión entre libical y std::chrono
    static TimePoint icalToTimePoint(const icaltimetype& tt);
    static icaltimetype timePointToIcal(const TimePoint& tp);
    static std::chrono::seconds durationBetween(const icaltimetype& start, const icaltimetype& end);
};

} // namespace model
