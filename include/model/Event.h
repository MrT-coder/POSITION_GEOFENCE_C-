// include/model/Event.h
#pragma once

#include <chrono>
#include <string>
#include "model/Message.h"
#include "model/Position.h"

namespace model {

/// Event: extiende Message con información de tiempo y referencia a posición, geocerca o mantenimiento
class Event : public Message {
public:
    using TimePoint = std::chrono::system_clock::time_point;

    // --- Nombres de eventos ---
    static inline constexpr const char* ALL_EVENTS                   = "allEvents";
    static inline constexpr const char* TYPE_COMMAND_RESULT          = "commandResult";
    static inline constexpr const char* TYPE_DEVICE_ONLINE           = "deviceOnline";
    static inline constexpr const char* TYPE_DEVICE_UNKNOWN          = "deviceUnknown";
    static inline constexpr const char* TYPE_DEVICE_OFFLINE          = "deviceOffline";
    static inline constexpr const char* TYPE_DEVICE_INACTIVE         = "deviceInactive";
    static inline constexpr const char* TYPE_QUEUED_COMMAND_SENT     = "queuedCommandSent";
    static inline constexpr const char* TYPE_DEVICE_MOVING           = "deviceMoving";
    static inline constexpr const char* TYPE_DEVICE_STOPPED          = "deviceStopped";
    static inline constexpr const char* TYPE_DEVICE_OVERSPEED        = "deviceOverspeed";
    static inline constexpr const char* TYPE_DEVICE_FUEL_DROP        = "deviceFuelDrop";
    static inline constexpr const char* TYPE_DEVICE_FUEL_INCREASE    = "deviceFuelIncrease";
    static inline constexpr const char* TYPE_GEOFENCE_ENTER          = "geofenceEnter";
    static inline constexpr const char* TYPE_GEOFENCE_EXIT           = "geofenceExit";
    static inline constexpr const char* TYPE_ALARM                   = "alarm";
    static inline constexpr const char* TYPE_IGNITION_ON            = "ignitionOn";
    static inline constexpr const char* TYPE_IGNITION_OFF           = "ignitionOff";
    static inline constexpr const char* TYPE_MAINTENANCE             = "maintenance";
    static inline constexpr const char* TYPE_TEXT_MESSAGE            = "textMessage";
    static inline constexpr const char* TYPE_DRIVER_CHANGED          = "driverChanged";
    static inline constexpr const char* TYPE_MEDIA                   = "media";

    // --- Constructores ---
    Event() = default;

    /// Crea un evento asociado a una posición ya existente
    Event(const std::string& type, const Position& position)
      : eventTime_(position.getDeviceTime())
      , positionId_(position.getId())
    {
        setType(type);
        setDeviceId(position.getDeviceId());
    }

    /// Crea un evento genérico para un dispositivo
    Event(const std::string& type, long deviceId)
      : eventTime_(std::chrono::system_clock::now())
      , positionId_(-1)
    {
        setType(type);
        setDeviceId(deviceId);
    }

    ~Event() = default;

    // --- Getters / Setters ---

    TimePoint getEventTime() const noexcept { return eventTime_; }
    void setEventTime(TimePoint t) noexcept { eventTime_ = t; }

    long getPositionId() const noexcept { return positionId_; }
    void setPositionId(long id) noexcept { positionId_ = id; }

    long getGeofenceId() const noexcept { return geofenceId_; }
    void setGeofenceId(long id) noexcept { geofenceId_ = id; }

    long getMaintenanceId() const noexcept { return maintenanceId_; }
    void setMaintenanceId(long id) noexcept { maintenanceId_ = id; }

private:
    TimePoint eventTime_{ std::chrono::system_clock::now() };
    long      positionId_{ -1 };
    long      geofenceId_{  0 };
    long      maintenanceId_{ 0 };
};

} // namespace model
