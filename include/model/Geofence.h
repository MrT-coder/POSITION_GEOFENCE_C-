#pragma once

#include "model/ExtendedModel.h"
#include "model/Schedulable.h"
#include "geofence/GeofenceGeometry.h"
#include <string>
#include <map>
#include <any>
#include <memory>

namespace model {

/// Geofence: extiende ExtendedModel e implementa calendario (Schedulable)
class Geofence : public ExtendedModel, public Schedulable {
public:
    Geofence() = default;

    /// Construye y parsea la geometría WKT
    Geofence(long calendarId,
             std::string name,
             std::string description,
             std::string area);

    // Schedulable
    long getCalendarId() const noexcept override;
    void setCalendarId(long calendarId) override;

    // Propiedades
    const std::string& getName() const noexcept;
    void setName(const std::string& name);

    const std::string& getDescription() const noexcept;
    void setDescription(const std::string& description);

    const std::string& getArea() const noexcept;
    void setArea(const std::string& area);

    const std::map<std::string, std::any>& getAttributes() const noexcept;
    void setAttributes(const std::map<std::string, std::any>& attributes);

    /// Geometría ya parseada (lanza si no existe)
    const geofence::GeofenceGeometry& getGeometry() const;
    /// Establece geometría y actualiza WKT
    void setGeometry(const geofence::GeofenceGeometry& geometry);

private:
    long calendarId_{0};
    std::string name_;
    std::string description_;
    std::string area_;
    std::map<std::string, std::any> attributes_;
    std::unique_ptr<geofence::GeofenceGeometry> geometry_;
};

} // namespace model
