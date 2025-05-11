// include/geofence/GeofenceCircle.h
#pragma once

#include "geofence/GeofenceGeometry.h"
#include <string>

namespace geofence {

/// Geofence de tipo círculo (radio en km)
class GeofenceCircle : public GeofenceGeometry {
public:
    GeofenceCircle() = default;
    explicit GeofenceCircle(const std::string& wkt) {
        fromWkt(wkt);
    }
    GeofenceCircle(double latitude, double longitude, double radius)
        : centerLatitude_(latitude)
        , centerLongitude_(longitude)
        , radiusKm_(radius) {}

    bool contains(double latitude, double longitude) const override;
    double area() const override;
    std::string toWkt() const override;
    void fromWkt(const std::string& wkt) override;

private:
    double distanceFromCenter(double latitude, double longitude) const;

    double centerLatitude_{0.0};
    double centerLongitude_{0.0};
    double radiusKm_{0.0};
};

} // namespace geofence
