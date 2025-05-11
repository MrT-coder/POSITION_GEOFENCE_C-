// include/geofence/GeofenceGeometryFactory.h
#pragma once

#include <memory>
#include <string>
#include "geofence/GeofenceGeometry.h"

namespace geofence {

/// Factory for parsing WKT-style area strings into geometry objects
class GeofenceGeometryFactory {
public:
    /// Parse an area string (WKT) and return the corresponding geometry
    /// \param area like "CIRCLE (...)", "POLYGON(...)" or "LINESTRING(...)"
    /// \throws std::invalid_argument if the prefix is unrecognized
    static std::unique_ptr<GeofenceGeometry> parse(const std::string& area);
};

} // namespace geofence
