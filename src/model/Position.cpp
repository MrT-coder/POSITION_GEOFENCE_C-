// src/model/Position.cpp
#include "model/Position.h"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/types.hpp>

namespace model
{

    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;

    // --- Constructores ---
    Position::Position(const std::string &protocol)
        : protocol_(protocol),
          serverTime_(std::chrono::system_clock::now()) {}

    Position::Position(const std::string &protocol,
                       TimePoint deviceTime,
                       TimePoint fixTime,
                       double latitude,
                       double longitude)
        : protocol_(protocol),
          serverTime_(std::chrono::system_clock::now()),
          deviceTime_(deviceTime),
          fixTime_(fixTime),
          latitude_(latitude),
          longitude_(longitude)
    {
        validateLatitude(latitude_);
        validateLongitude(longitude_);
    }

    // --- Getters / Setters ---
    const std::string &Position::getProtocol() const noexcept { return protocol_; }
    void Position::setProtocol(const std::string &p) { protocol_ = p; }

    Position::TimePoint Position::getServerTime() const noexcept { return serverTime_; }
    void Position::setServerTime(TimePoint t) { serverTime_ = t; }

    Position::TimePoint Position::getDeviceTime() const noexcept { return deviceTime_; }
    void Position::setDeviceTime(TimePoint t) { deviceTime_ = t; }

    Position::TimePoint Position::getFixTime() const noexcept { return fixTime_; }
    void Position::setFixTime(TimePoint t) { fixTime_ = t; }

    void Position::setTime(TimePoint t)
    {
        deviceTime_ = t;
        fixTime_ = t;
    }

    bool Position::getOutdated() const noexcept { return outdated_; }
    void Position::setOutdated(bool o) noexcept { outdated_ = o; }

    bool Position::getValid() const noexcept { return valid_; }
    void Position::setValid(bool v) noexcept { valid_ = v; }

    double Position::getLatitude() const noexcept { return latitude_; }
    void Position::setLatitude(double lat)
    {
        validateLatitude(lat);
        latitude_ = lat;
    }

    double Position::getLongitude() const noexcept { return longitude_; }
    void Position::setLongitude(double lon)
    {
        validateLongitude(lon);
        longitude_ = lon;
    }

    double Position::getAltitude() const noexcept { return altitude_; }
    void Position::setAltitude(double a) noexcept { altitude_ = a; }

    double Position::getSpeed() const noexcept { return speed_; }
    void Position::setSpeed(double s) noexcept { speed_ = s; }

    double Position::getCourse() const noexcept { return course_; }
    void Position::setCourse(double c) noexcept { course_ = c; }

    const std::string &Position::getAddress() const noexcept { return address_; }
    void Position::setAddress(const std::string &addr) { address_ = addr; }

    double Position::getAccuracy() const noexcept { return accuracy_; }
    void Position::setAccuracy(double a) noexcept { accuracy_ = a; }

    const Network &Position::getNetwork() const noexcept { return network_; }
    void Position::setNetwork(const Network &net) noexcept { network_ = net; }

    const std::vector<long> &Position::getGeofenceIds() const noexcept { return geofenceIds_; }
    void Position::setGeofenceIds(const std::vector<long> &ids)
    {
        geofenceIds_ = ids;
    }

    // --- Serialización a BSON ---
    bsoncxx::document::value Position::to_bson() const
    {
        document doc{};

        // Campos de BaseModel / Message
        doc << "_id" << getId()
            << "deviceId" << getDeviceId()
            << "type" << getType();

        // Campos de Position
        doc << "protocol" << protocol_
            << "serverTime" << bsoncxx::types::b_date{serverTime_}
            << "deviceTime" << bsoncxx::types::b_date{deviceTime_}
            << "fixTime" << bsoncxx::types::b_date{fixTime_}
            << "latitude" << latitude_
            << "longitude" << longitude_
            << "altitude" << altitude_
            << "speed" << speed_
            << "course" << course_
            << "address" << address_
            << "accuracy" << accuracy_
            << "valid" << valid_
            << "outdated" << outdated_;

        // Subdocumento Network
        doc << "network" << [&](auto ec)
        {
            auto sub = ec.start_document();
            sub << "mcc" << network_.getMcc()
                << "mnc" << network_.getMnc()
                << "lac" << network_.getLac()
                << "cell" << network_.getCell();
            sub.end_document();
        };

        // Array de geofenceIds
        doc << "geofenceIds" << [&](auto ec)
        {
            auto arr = ec.start_array();
            for (auto id : geofenceIds_)
                arr << id;
            arr.end_array();
        };

        // Atributos dinámicos de ExtendedModel
        for (auto &[k, v] : getAttributes())
        {
            doc << k << v;
        }

        return doc << finalize;
    }

    // --- Validadores ---
    void Position::validateLatitude(double lat)
    {
        if (lat < -90.0 || lat > 90.0)
        {
            throw std::out_of_range("Latitude out of range");
        }
    }

    void Position::validateLongitude(double lon)
    {
        if (lon < -180.0 || lon > 180.0)
        {
            throw std::out_of_range("Longitude out of range");
        }
    }

} // namespace model
