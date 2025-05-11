#include "model/Geofence.h"
#include "geofence/GeofenceGeometryFactory.h"
#include <stdexcept>

namespace model {

Geofence::Geofence(long calendarId,
                   std::string name,
                   std::string description,
                   std::string area)
    : calendarId_(calendarId),
      name_(std::move(name)),
      description_(std::move(description)) {
    setArea(area);
}

long Geofence::getCalendarId() const noexcept {
    return calendarId_;
}

void Geofence::setCalendarId(long calendarId) {
    calendarId_ = calendarId;
}

const std::string& Geofence::getName() const noexcept {
    return name_;
}

void Geofence::setName(const std::string& name) {
    name_ = name;
}

const std::string& Geofence::getDescription() const noexcept {
    return description_;
}

void Geofence::setDescription(const std::string& description) {
    description_ = description;
}

const std::string& Geofence::getArea() const noexcept {
    return area_;
}

void Geofence::setArea(const std::string& area) {
    // Parsea WKT y lanza std::runtime_error si falla
    auto geom = geofence::GeofenceGeometryFactory::parse(area);
    geometry_ = std::make_unique<geofence::GeofenceGeometry>(std::move(geom));
    area_     = area;
}

const std::map<std::string, std::any>& Geofence::getAttributes() const noexcept {
    return attributes_;
}

void Geofence::setAttributes(const std::map<std::string, std::any>& attributes) {
    attributes_ = attributes;
}

const geofence::GeofenceGeometry& Geofence::getGeometry() const {
    if (!geometry_) {
        throw std::runtime_error("Geofence geometry not set");
    }
    return *geometry_;
}

void Geofence::setGeometry(const geofence::GeofenceGeometry& geometry) {
    geometry_ = std::make_unique<geofence::GeofenceGeometry>(geometry);
    area_     = geometry.toWkt();
}

} // namespace model
