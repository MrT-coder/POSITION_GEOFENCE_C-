// include/geofence/GeofencePolyline.h
#pragma once

#include "GeofenceGeometry.h"
#include <vector>
#include <string>

namespace geofence {

/// Polilínea geocerca (no tiene área; contiene puntos si está a menos de un umbral)
class GeofencePolyline : public GeofenceGeometry {
public:
    GeofencePolyline() = default;
    explicit GeofencePolyline(const std::string& wkt) {
        fromWkt(wkt);
    }

    bool contains(double latitude, double longitude) const override;
    double area()     const override { return 0.0; }
    std::string toWkt()      const override;
    void        fromWkt(const std::string& wkt) override;

private:
    static constexpr double kDistanceThresholdKm = 0.01;  // 10 m ≈ 0.01 km
    static constexpr double kDegreeToKm            = 111.0; // 1 grado ≈ 111 km

    std::vector<Coordinate> coordinates_;

    double distanceToLine(double lat, double lon,
                          double lat1, double lon1,
                          double lat2, double lon2) const;
};

} // namespace geofence
