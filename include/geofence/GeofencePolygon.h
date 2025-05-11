#pragma once

#include "GeofenceGeometry.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>

namespace geofence {

/// Polígono definido por una lista de coordenadas (lat, lon)
class GeofencePolygon : public GeofenceGeometry {
public:
    GeofencePolygon() = default;
    explicit GeofencePolygon(const std::string& wkt) {
        fromWkt(wkt);
    }

    /// área con la fórmula de “shoelace”
    double calculateArea() const ;

    /// test de punto dentro con ray-casting
    bool containsPoint(void* config, void* geofence, double latitude, double longitude) const ;

    /// devuelve el WKT “POLYGON ((lat lon, lat lon, …))”
    std::string toWkt() const override;

    /// parsea WKT; lanza std::invalid_argument si no es válido
    void fromWkt(const std::string& wkt) override;

private:
    std::vector<Coordinate> coordinates_;
};

} // namespace geofence
