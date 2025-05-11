// include/model/Command.h
#pragma once

#include <string>
#include "model/BaseCommand.h"

namespace model {

/// Command: extiende BaseCommand con tipos y claves estáticas
class Command : public BaseCommand {
public:
    // Tipos de comando
    static inline constexpr const char* TYPE_CUSTOM               = "custom";
    static inline constexpr const char* TYPE_IDENTIFICATION       = "deviceIdentification";
    static inline constexpr const char* TYPE_POSITION_SINGLE      = "positionSingle";
    static inline constexpr const char* TYPE_POSITION_PERIODIC    = "positionPeriodic";
    static inline constexpr const char* TYPE_POSITION_STOP        = "positionStop";
    static inline constexpr const char* TYPE_ENGINE_STOP          = "engineStop";
    static inline constexpr const char* TYPE_ENGINE_RESUME        = "engineResume";
    static inline constexpr const char* TYPE_ALARM_ARM            = "alarmArm";
    static inline constexpr const char* TYPE_ALARM_DISARM         = "alarmDisarm";
    static inline constexpr const char* TYPE_ALARM_DISMISS        = "alarmDismiss";
    static inline constexpr const char* TYPE_SET_TIMEZONE         = "setTimezone";
    static inline constexpr const char* TYPE_REQUEST_PHOTO        = "requestPhoto";
    static inline constexpr const char* TYPE_POWER_OFF            = "powerOff";
    static inline constexpr const char* TYPE_REBOOT_DEVICE        = "rebootDevice";
    static inline constexpr const char* TYPE_FACTORY_RESET        = "factoryReset";
    static inline constexpr const char* TYPE_SEND_SMS             = "sendSms";
    static inline constexpr const char* TYPE_SEND_USSD            = "sendUssd";
    static inline constexpr const char* TYPE_SOS_NUMBER           = "sosNumber";
    static inline constexpr const char* TYPE_SILENCE_TIME         = "silenceTime";
    static inline constexpr const char* TYPE_SET_PHONEBOOK        = "setPhonebook";
    static inline constexpr const char* TYPE_MESSAGE              = "message";
    static inline constexpr const char* TYPE_VOICE_MESSAGE        = "voiceMessage";
    static inline constexpr const char* TYPE_OUTPUT_CONTROL       = "outputControl";
    static inline constexpr const char* TYPE_VOICE_MONITORING     = "voiceMonitoring";
    static inline constexpr const char* TYPE_SET_AGPS             = "setAgps";
    static inline constexpr const char* TYPE_SET_INDICATOR        = "setIndicator";
    static inline constexpr const char* TYPE_CONFIGURATION        = "configuration";
    static inline constexpr const char* TYPE_GET_VERSION          = "getVersion";
    static inline constexpr const char* TYPE_FIRMWARE_UPDATE      = "firmwareUpdate";
    static inline constexpr const char* TYPE_SET_CONNECTION       = "setConnection";
    static inline constexpr const char* TYPE_SET_ODOMETER         = "setOdometer";
    static inline constexpr const char* TYPE_GET_MODEM_STATUS     = "getModemStatus";
    static inline constexpr const char* TYPE_GET_DEVICE_STATUS    = "getDeviceStatus";
    static inline constexpr const char* TYPE_SET_SPEED_LIMIT      = "setSpeedLimit";
    static inline constexpr const char* TYPE_MODE_POWER_SAVING    = "modePowerSaving";
    static inline constexpr const char* TYPE_MODE_DEEP_SLEEP      = "modeDeepSleep";

    static inline constexpr const char* TYPE_ALARM_GEOFENCE       = "alarmGeofence";
    static inline constexpr const char* TYPE_ALARM_BATTERY        = "alarmBattery";
    static inline constexpr const char* TYPE_ALARM_SOS            = "alarmSos";
    static inline constexpr const char* TYPE_ALARM_REMOVE         = "alarmRemove";
    static inline constexpr const char* TYPE_ALARM_CLOCK          = "alarmClock";
    static inline constexpr const char* TYPE_ALARM_SPEED          = "alarmSpeed";
    static inline constexpr const char* TYPE_ALARM_FALL           = "alarmFall";
    static inline constexpr const char* TYPE_ALARM_VIBRATION      = "alarmVibration";

    // Claves adicionales
    static inline constexpr const char* KEY_UNIQUE_ID     = "uniqueId";
    static inline constexpr const char* KEY_FREQUENCY     = "frequency";
    static inline constexpr const char* KEY_LANGUAGE      = "language";
    static inline constexpr const char* KEY_TIMEZONE      = "timezone";
    static inline constexpr const char* KEY_DEVICE_PASSWORD = "devicePassword";
    static inline constexpr const char* KEY_RADIUS        = "radius";
    static inline constexpr const char* KEY_MESSAGE       = "message";
    static inline constexpr const char* KEY_ENABLE        = "enable";
    static inline constexpr const char* KEY_DATA          = "data";
    static inline constexpr const char* KEY_INDEX         = "index";
    static inline constexpr const char* KEY_PHONE         = "phone";
    static inline constexpr const char* KEY_SERVER        = "server";
    static inline constexpr const char* KEY_PORT          = "port";
    static inline constexpr const char* KEY_NO_QUEUE      = "noQueue";

    Command() = default;
    ~Command()  = default;

    // Descripción opcional
    const std::string& getDescription() const noexcept { return description_; }
    void setDescription(const std::string& d) { description_ = d; }

private:
    std::string description_;
};

} // namespace model
