// include/model/Position.h
#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <stdexcept>

#include "model/Message.h"
#include "model/Network.h"

namespace model {

/// Position: extiende Message con información de geolocalización y metadatos
class Position : public Message {
public:
    using TimePoint = std::chrono::system_clock::time_point;

    // Campos estáticos de clave para atributos extendidos
    static inline constexpr const char* KEY_ORIGINAL         = "raw";
    static inline constexpr const char* KEY_INDEX            = "index";
    static inline constexpr const char* KEY_HDOP             = "hdop";
    static inline constexpr const char* KEY_VDOP             = "vdop";
    static inline constexpr const char* KEY_PDOP             = "pdop";
    static inline constexpr const char* KEY_SATELLITES       = "sat";
    static inline constexpr const char* KEY_SATELLITES_VISIBLE = "satVisible";
    static inline constexpr const char* KEY_RSSI             = "rssi";
    static inline constexpr const char* KEY_GPS              = "gps";
    static inline constexpr const char* KEY_ROAMING          = "roaming";
    static inline constexpr const char* KEY_EVENT            = "event";
    static inline constexpr const char* KEY_ALARM            = "alarm";
    static inline constexpr const char* KEY_STATUS           = "status";
    static inline constexpr const char* KEY_ODOMETER         = "odometer";
    static inline constexpr const char* KEY_ODOMETER_SERVICE = "serviceOdometer";
    static inline constexpr const char* KEY_ODOMETER_TRIP    = "tripOdometer";
    static inline constexpr const char* KEY_HOURS            = "hours";
    static inline constexpr const char* KEY_STEPS            = "steps";
    static inline constexpr const char* KEY_HEART_RATE       = "heartRate";
    static inline constexpr const char* KEY_INPUT            = "input";
    static inline constexpr const char* KEY_OUTPUT           = "output";
    static inline constexpr const char* KEY_IMAGE            = "image";
    static inline constexpr const char* KEY_VIDEO            = "video";
    static inline constexpr const char* KEY_AUDIO            = "audio";
    static inline constexpr const char* KEY_POWER            = "power";
    static inline constexpr const char* KEY_BATTERY          = "battery";
    static inline constexpr const char* KEY_BATTERY_LEVEL    = "batteryLevel";
    static inline constexpr const char* KEY_FUEL_LEVEL       = "fuel";
    static inline constexpr const char* KEY_FUEL_USED        = "fuelUsed";
    static inline constexpr const char* KEY_FUEL_CONSUMPTION = "fuelConsumption";
    static inline constexpr const char* KEY_VERSION_FW       = "versionFw";
    static inline constexpr const char* KEY_VERSION_HW       = "versionHw";
    static inline constexpr const char* KEY_TYPE             = "type";
    static inline constexpr const char* KEY_IGNITION         = "ignition";
    static inline constexpr const char* KEY_FLAGS            = "flags";
    static inline constexpr const char* KEY_ANTENNA          = "antenna";
    static inline constexpr const char* KEY_CHARGE           = "charge";
    static inline constexpr const char* KEY_IP               = "ip";
    static inline constexpr const char* KEY_ARCHIVE          = "archive";
    static inline constexpr const char* KEY_DISTANCE         = "distance";
    static inline constexpr const char* KEY_TOTAL_DISTANCE   = "totalDistance";
    static inline constexpr const char* KEY_RPM              = "rpm";
    static inline constexpr const char* KEY_VIN              = "vin";
    static inline constexpr const char* KEY_APPROXIMATE      = "approximate";
    static inline constexpr const char* KEY_THROTTLE         = "throttle";
    static inline constexpr const char* KEY_MOTION           = "motion";
    static inline constexpr const char* KEY_ARMED            = "armed";
    static inline constexpr const char* KEY_GEOFENCE         = "geofence";
    static inline constexpr const char* KEY_ACCELERATION     = "acceleration";
    static inline constexpr const char* KEY_HUMIDITY         = "humidity";
    static inline constexpr const char* KEY_DEVICE_TEMP      = "deviceTemp";
    static inline constexpr const char* KEY_COOLANT_TEMP     = "coolantTemp";
    static inline constexpr const char* KEY_ENGINE_LOAD      = "engineLoad";
    static inline constexpr const char* KEY_ENGINE_TEMP      = "engineTemp";
    static inline constexpr const char* KEY_OPERATOR         = "operator";
    static inline constexpr const char* KEY_COMMAND          = "command";
    static inline constexpr const char* KEY_BLOCKED          = "blocked";
    static inline constexpr const char* KEY_LOCK             = "lock";
    static inline constexpr const char* KEY_DOOR             = "door";
    static inline constexpr const char* KEY_AXLE_WEIGHT      = "axleWeight";
    static inline constexpr const char* KEY_G_SENSOR         = "gSensor";
    static inline constexpr const char* KEY_ICCID            = "iccid";
    static inline constexpr const char* KEY_PHONE            = "phone";
    static inline constexpr const char* KEY_SPEED_LIMIT      = "speedLimit";
    static inline constexpr const char* KEY_DRIVING_TIME     = "drivingTime";
    static inline constexpr const char* KEY_DTCS             = "dtcs";
    static inline constexpr const char* KEY_OBD_SPEED        = "obdSpeed";
    static inline constexpr const char* KEY_OBD_ODOMETER     = "obdOdometer";
    static inline constexpr const char* KEY_RESULT           = "result";
    static inline constexpr const char* KEY_DRIVER_UNIQUE_ID = "driverUniqueId";
    static inline constexpr const char* KEY_CARD             = "card";
    static inline constexpr const char* PREFIX_TEMP          = "temp";
    static inline constexpr const char* PREFIX_ADC           = "adc";
    static inline constexpr const char* PREFIX_IO            = "io";
    static inline constexpr const char* PREFIX_COUNT         = "count";
    static inline constexpr const char* PREFIX_IN            = "in";
    static inline constexpr const char* PREFIX_OUT           = "out";
    // Alarmas
    static inline constexpr const char* ALARM_GENERAL        = "general";
    static inline constexpr const char* ALARM_SOS            = "sos";
    static inline constexpr const char* ALARM_VIBRATION      = "vibration";
    static inline constexpr const char* ALARM_MOVEMENT       = "movement";
    static inline constexpr const char* ALARM_LOW_SPEED      = "lowspeed";
    static inline constexpr const char* ALARM_OVERSPEED      = "overspeed";
    static inline constexpr const char* ALARM_FALL_DOWN      = "fallDown";
    static inline constexpr const char* ALARM_LOW_POWER      = "lowPower";
    static inline constexpr const char* ALARM_LOW_BATTERY    = "lowBattery";
    static inline constexpr const char* ALARM_FAULT          = "fault";
    static inline constexpr const char* ALARM_POWER_OFF      = "powerOff";
    static inline constexpr const char* ALARM_POWER_ON       = "powerOn";
    static inline constexpr const char* ALARM_DOOR           = "door";
    static inline constexpr const char* ALARM_LOCK           = "lock";
    static inline constexpr const char* ALARM_UNLOCK         = "unlock";
    static inline constexpr const char* ALARM_GEOFENCE       = "geofence";
    static inline constexpr const char* ALARM_GEOFENCE_ENTER = "geofenceEnter";
    static inline constexpr const char* ALARM_GEOFENCE_EXIT  = "geofenceExit";
    static inline constexpr const char* ALARM_GPS_ANTENNA_CUT= "gpsAntennaCut";
    static inline constexpr const char* ALARM_ACCIDENT       = "accident";
    static inline constexpr const char* ALARM_TOW            = "tow";
    static inline constexpr const char* ALARM_IDLE           = "idle";
    static inline constexpr const char* ALARM_HIGH_RPM       = "highRpm";
    static inline constexpr const char* ALARM_ACCELERATION   = "hardAcceleration";
    static inline constexpr const char* ALARM_BRAKING        = "hardBraking";
    static inline constexpr const char* ALARM_CORNERING      = "hardCornering";
    static inline constexpr const char* ALARM_LANE_CHANGE    = "laneChange";
    static inline constexpr const char* ALARM_FATIGUE_DRIVING= "fatigueDriving";
    static inline constexpr const char* ALARM_POWER_CUT      = "powerCut";
    static inline constexpr const char* ALARM_POWER_RESTORED = "powerRestored";
    static inline constexpr const char* ALARM_JAMMING        = "jamming";
    static inline constexpr const char* ALARM_TEMPERATURE    = "temperature";
    static inline constexpr const char* ALARM_PARKING        = "parking";
    static inline constexpr const char* ALARM_BONNET         = "bonnet";
    static inline constexpr const char* ALARM_FOOT_BRAKE     = "footBrake";
    static inline constexpr const char* ALARM_FUEL_LEAK      = "fuelLeak";
    static inline constexpr const char* ALARM_TAMPERING      = "tampering";
    static inline constexpr const char* ALARM_REMOVING       = "removing";

    // Constructores
    Position() = default;
    explicit Position(const std::string& protocol)
      : protocol_(protocol)
      , serverTime_(std::chrono::system_clock::now()) {}
    Position(const std::string& protocol,
             TimePoint deviceTime,
             TimePoint fixTime,
             double latitude,
             double longitude)
      : protocol_(protocol)
      , serverTime_(std::chrono::system_clock::now())
      , deviceTime_(deviceTime)
      , fixTime_(fixTime)
      , latitude_(latitude)
      , longitude_(longitude) {
        validateLatitude(latitude_);
        validateLongitude(longitude_);
    }

    // Getters / Setters
    const std::string& getProtocol() const noexcept { return protocol_; }
    void setProtocol(const std::string& p) { protocol_ = p; }

    TimePoint getServerTime() const noexcept { return serverTime_; }
    void setServerTime(TimePoint t) { serverTime_ = t; }

    TimePoint getDeviceTime() const noexcept { return deviceTime_; }
    void setDeviceTime(TimePoint t) { deviceTime_ = t; }

    TimePoint getFixTime() const noexcept { return fixTime_; }
    void setFixTime(TimePoint t) { fixTime_ = t; }

    void setTime(TimePoint t) {
        setDeviceTime(t);
        setFixTime(t);
    }

    bool getOutdated() const noexcept { return outdated_; }
    void setOutdated(bool o) noexcept { outdated_ = o; }

    bool getValid() const noexcept { return valid_; }
    void setValid(bool v) noexcept { valid_ = v; }

    double getLatitude() const noexcept { return latitude_; }
    void setLatitude(double lat) {
        validateLatitude(lat);
        latitude_ = lat;
    }

    double getLongitude() const noexcept { return longitude_; }
    void setLongitude(double lon) {
        validateLongitude(lon);
        longitude_ = lon;
    }

    double getAltitude() const noexcept { return altitude_; }
    void setAltitude(double a) noexcept { altitude_ = a; }

    double getSpeed() const noexcept { return speed_; }
    void setSpeed(double s) noexcept { speed_ = s; }

    double getCourse() const noexcept { return course_; }
    void setCourse(double c) noexcept { course_ = c; }

    const std::string& getAddress() const noexcept { return address_; }
    void setAddress(const std::string& addr) { address_ = addr; }

    double getAccuracy() const noexcept { return accuracy_; }
    void setAccuracy(double a) noexcept { accuracy_ = a; }

    const Network& getNetwork() const noexcept { return network_; }
    void setNetwork(const Network& net) noexcept { network_ = net; }

    const std::vector<long>& getGeofenceIds() const noexcept { return geofenceIds_; }
    void setGeofenceIds(const std::vector<long>& ids) {
        geofenceIds_ = ids;
    }




private:
    static void validateLatitude(double lat) {
        if (lat < -90.0 || lat > 90.0) {
            throw std::out_of_range("Latitude out of range");
        }
    }
    static void validateLongitude(double lon) {
        if (lon < -180.0 || lon > 180.0) {
            throw std::out_of_range("Longitude out of range");
        }
    }

    std::string protocol_;
    TimePoint serverTime_{std::chrono::system_clock::now()};
    TimePoint deviceTime_{};
    TimePoint fixTime_{};
    bool outdated_{false};
    bool valid_{false};
    double latitude_{0.0};
    double longitude_{0.0};
    double altitude_{0.0};
    double speed_{0.0};
    double course_{0.0};
    std::string address_;
    double accuracy_{0.0};
    Network network_{};
    std::vector<long> geofenceIds_;
};

} // namespace model
