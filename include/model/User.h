// include/model/User.h
#pragma once

#include "model/ExtendedModel.h"
#include "model/UserRestrictions.h"
#include "model/Disableable.h"

#include <string>
#include <chrono>

namespace model {

/// Representa un usuario con restricciones, estado y metadatos opcionales
class User : public ExtendedModel, public UserRestrictions, public Disableable {
public:
    using TimePoint = std::chrono::system_clock::time_point;

    // --- Nombre, login y datos de contacto ---
    const std::string& getName() const noexcept { return name_; }
    void setName(const std::string& v) { name_ = v; }

    const std::string& getLogin() const noexcept { return login_; }
    void setLogin(const std::string& v) { login_ = v; }

    const std::string& getEmail() const noexcept { return email_; }
    void setEmail(const std::string& v) { email_ = v; }

    const std::string& getPhone() const noexcept { return phone_; }
    void setPhone(const std::string& v) { phone_ = v; }

    // --- Restricciones de solo lectura ---
    bool getReadonly() const override { return readonly_; }
    void setReadonly(bool v)     { readonly_ = v; }

    bool getDeviceReadonly() const override { return deviceReadonly_; }
    void setDeviceReadonly(bool v)          { deviceReadonly_ = v; }

    // --- Administración y permisos ---
    bool getAdministrator() const noexcept { return administrator_; }
    void setAdministrator(bool v)         { administrator_ = v; }

    bool getLimitCommands() const override { return limitCommands_; }
    void setLimitCommands(bool v)          { limitCommands_ = v; }

    bool getDisableReports() const override { return disableReports_; }
    void setDisableReports(bool v)          { disableReports_ = v; }

    bool getFixedEmail() const override { return fixedEmail_; }
    void setFixedEmail(bool v)          { fixedEmail_ = v; }

    bool getManager() const noexcept { return userLimit_ != 0; }

    // --- Configuración de mapa y geolocalización ---
    const std::string& getMap() const noexcept { return map_; }
    void setMap(const std::string& v)         { map_ = v; }

    double getLatitude() const noexcept { return latitude_; }
    void setLatitude(double v)          { latitude_ = v; }

    double getLongitude() const noexcept { return longitude_; }
    void setLongitude(double v)          { longitude_ = v; }

    int getZoom() const noexcept { return zoom_; }
    void setZoom(int v)          { zoom_ = v; }

    const std::string& getCoordinateFormat() const noexcept { return coordinateFormat_; }
    void setCoordinateFormat(const std::string& v)          { coordinateFormat_ = v; }

    // --- Estado y caducidad ---
    bool getDisabled() const override { return disabled_; }
    void setDisabled(bool v)         { disabled_ = v; }

    TimePoint getExpirationTime() const override { return expirationTime_; }
    void setExpirationTime(TimePoint t)          { expirationTime_ = t; }

    // --- Límites de usuario y dispositivo ---
    int getDeviceLimit() const noexcept { return deviceLimit_; }
    void setDeviceLimit(int v)         { deviceLimit_ = v; }

    int getUserLimit() const noexcept { return userLimit_; }
    void setUserLimit(int v)         { userLimit_ = v; }

    // --- Capa adicional de UI/POI/TOTP/temporal ---
    const std::string& getPoiLayer() const noexcept { return poiLayer_; }
    void setPoiLayer(const std::string& v)          { poiLayer_ = v; }

    const std::string& getTotpKey() const noexcept { return totpKey_; }
    void setTotpKey(const std::string& v)          { totpKey_ = v; }

    bool getTemporary() const noexcept { return temporary_; }
    void setTemporary(bool v)          { temporary_ = v; }

private:
    std::string name_;
    std::string login_;
    std::string email_;
    std::string phone_;

    bool readonly_{false};
    bool deviceReadonly_{false};
    bool administrator_{false};
    bool limitCommands_{false};
    bool disableReports_{false};
    bool fixedEmail_{false};

    std::string map_;
    double latitude_{0.0};
    double longitude_{0.0};
    int zoom_{0};
    std::string coordinateFormat_;

    bool disabled_{false};
    TimePoint expirationTime_{};

    int deviceLimit_{0};
    int userLimit_{0};

    std::string poiLayer_;
    std::string totpKey_;
    bool temporary_{false};
};

} // namespace model
