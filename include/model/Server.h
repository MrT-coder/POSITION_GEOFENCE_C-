// include/model/Server.h
#pragma once

#include "model/ExtendedModel.h"
#include "model/UserRestrictions.h"

#include <string>
#include <vector>

namespace model {

/// Mapea el modelo Java com.traccar.PositionGeofence.modelo.Server
class Server : public ExtendedModel, public UserRestrictions {
public:
    Server() = default;

    // — registration —
    bool getRegistration() const noexcept { return registration_; }
    void setRegistration(bool v) noexcept { registration_ = v; }

    // — readonly (UserRestrictions) —
    bool getReadonly() const noexcept override { return readonly_; }
    void setReadonly(bool v) noexcept { readonly_ = v; }

    // — deviceReadonly (UserRestrictions) —
    bool getDeviceReadonly() const noexcept override { return deviceReadonly_; }
    void setDeviceReadonly(bool v) noexcept { deviceReadonly_ = v; }

    // — map URLs & keys —
    const std::string& getMap() const noexcept { return map_; }
    void setMap(const std::string& v) { map_ = v; }

    const std::string& getBingKey() const noexcept { return bingKey_; }
    void setBingKey(const std::string& v) { bingKey_ = v; }

    const std::string& getMapUrl() const noexcept { return mapUrl_; }
    void setMapUrl(const std::string& v) { mapUrl_ = v; }

    const std::string& getOverlayUrl() const noexcept { return overlayUrl_; }
    void setOverlayUrl(const std::string& v) { overlayUrl_ = v; }

    // — coordenadas y zoom —
    double getLatitude() const noexcept { return latitude_; }
    void setLatitude(double v) noexcept { latitude_ = v; }

    double getLongitude() const noexcept { return longitude_; }
    void setLongitude(double v) noexcept { longitude_ = v; }

    int getZoom() const noexcept { return zoom_; }
    void setZoom(int v) noexcept { zoom_ = v; }

    bool getForceSettings() const noexcept { return forceSettings_; }
    void setForceSettings(bool v) noexcept { forceSettings_ = v; }

    const std::string& getCoordinateFormat() const noexcept { return coordinateFormat_; }
    void setCoordinateFormat(const std::string& v) { coordinateFormat_ = v; }

    // — limitCommands (UserRestrictions) —
    bool getLimitCommands() const noexcept override { return limitCommands_; }
    void setLimitCommands(bool v) noexcept { limitCommands_ = v; }

    // — disableReports (UserRestrictions) —
    bool getDisableReports() const noexcept override { return disableReports_; }
    void setDisableReports(bool v) noexcept { disableReports_ = v; }

    // — fixedEmail (UserRestrictions) —
    bool getFixedEmail() const noexcept override { return fixedEmail_; }
    void setFixedEmail(bool v) noexcept { fixedEmail_ = v; }

    // — anuncio —
    const std::string& getAnnouncement() const noexcept { return announcement_; }
    void setAnnouncement(const std::string& v) { announcement_ = v; }

    // — email/text/geocoder flags —
    bool getEmailEnabled() const noexcept { return emailEnabled_; }
    void setEmailEnabled(bool v) noexcept { emailEnabled_ = v; }

    bool getTextEnabled() const noexcept { return textEnabled_; }
    void setTextEnabled(bool v) noexcept { textEnabled_ = v; }

    bool getGeocoderEnabled() const noexcept { return geocoderEnabled_; }
    void setGeocoderEnabled(bool v) noexcept { geocoderEnabled_ = v; }

    // — espacio en disco por secciones —
    const std::vector<long>& getStorageSpace() const noexcept { return storageSpace_; }
    void setStorageSpace(const std::vector<long>& v) { storageSpace_ = v; }

    // — flags de servidor nuevo y OpenID —
    bool getNewServer() const noexcept { return newServer_; }
    void setNewServer(bool v) noexcept { newServer_ = v; }

    bool getOpenIdEnabled() const noexcept { return openIdEnabled_; }
    void setOpenIdEnabled(bool v) noexcept { openIdEnabled_ = v; }

    bool getOpenIdForce() const noexcept { return openIdForce_; }
    void setOpenIdForce(bool v) noexcept { openIdForce_ = v; }

private:
    bool registration_{false};
    bool readonly_{false};
    bool deviceReadonly_{false};
    std::string map_;
    std::string bingKey_;
    std::string mapUrl_;
    std::string overlayUrl_;
    double latitude_{0.0};
    double longitude_{0.0};
    int zoom_{0};
    bool forceSettings_{false};
    std::string coordinateFormat_;
    bool limitCommands_{false};
    bool disableReports_{false};
    bool fixedEmail_{false};
    std::string announcement_;
    bool emailEnabled_{false};
    bool textEnabled_{false};
    bool geocoderEnabled_{false};
    std::vector<long> storageSpace_;
    bool newServer_{false};
    bool openIdEnabled_{false};
    bool openIdForce_{false};
};

} // namespace model
