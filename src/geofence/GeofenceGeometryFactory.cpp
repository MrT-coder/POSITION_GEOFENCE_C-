// src/geofence/GeofenceGeometryFactory.cpp

#include "geofence/GeofenceGeometryFactory.h"
#include "geofence/GeofenceCircle.h"
#include "geofence/GeofencePolygon.h"
#include "geofence/GeofencePolyline.h"
#include <stdexcept>

namespace geofence {

std::unique_ptr<GeofenceGeometry> GeofenceGeometryFactory::parse(const std::string& area) {
    // Comprobamos prefijos
    if (area.rfind("CIRCLE", 0) == 0) {
        return std::make_unique<GeofenceCircle>(area);
    } else if (area.rfind("POLYGON", 0) == 0) {
        return std::make_unique<GeofencePolygon>(area);
    } else if (area.rfind("LINESTRING", 0) == 0) {
        return std::make_unique<GeofencePolyline>(area);
    }
    throw std::invalid_argument("Unknown geometry type: " + area);
}

} // namespace geofence
