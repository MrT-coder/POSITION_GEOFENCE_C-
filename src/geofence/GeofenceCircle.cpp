// src/geofence/GeofenceCircle.cpp
#define _USE_MATH_DEFINES

#include "geofence/GeofenceCircle.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <stdexcept>


namespace geofence {
static constexpr double kEarthRadiusKm = 6371.0;

bool GeofenceCircle::contains(double latitude, double longitude) const {
    return distanceFromCenter(latitude, longitude) <= radiusKm_;
}

double GeofenceCircle::area() const {
    return M_PI * radiusKm_ * radiusKm_;
}

double GeofenceCircle::distanceFromCenter(double latitude, double longitude) const {
    const double dLat = (latitude - centerLatitude_) * M_PI / 180.0;
    const double dLon = (longitude - centerLongitude_) * M_PI / 180.0;
    const double lat1 = centerLatitude_ * M_PI / 180.0;
    const double lat2 = latitude * M_PI / 180.0;
    const double a = std::sin(dLat/2) * std::sin(dLat/2)
                   + std::cos(lat1) * std::cos(lat2)
                   * std::sin(dLon/2) * std::sin(dLon/2);
    const double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return kEarthRadiusKm * c;
}

std::string GeofenceCircle::toWkt() const {
    std::ostringstream oss;
    oss << "CIRCLE (" << centerLatitude_ << " " << centerLongitude_ << ", ";
    // formato "0.#": sin decimales si es entero, 1 decimal si no
    if (std::floor(radiusKm_) == radiusKm_) {
        oss << static_cast<long long>(radiusKm_);
    } else {
        oss << std::fixed << std::setprecision(1) << radiusKm_;
    }
    oss << ")";
    return oss.str();
}

void GeofenceCircle::fromWkt(const std::string& wkt) {
    // Ejemplo: "CIRCLE (12.34 56.78, 2.5)"
    auto pos1 = wkt.find('(');
    auto pos2 = wkt.rfind(')');
    if (pos1 == std::string::npos || pos2 == std::string::npos || pos2 <= pos1)
        throw WktParseException("Invalid CIRCLE WKT");

    auto content = wkt.substr(pos1 + 1, pos2 - pos1 - 1);
    auto comma = content.find(',');
    if (comma == std::string::npos)
        throw WktParseException("Missing comma");

    std::string coords = content.substr(0, comma);
    std::string rad    = content.substr(comma + 1);

    // parse coords
    std::istringstream iss(coords);
    if (!(iss >> centerLatitude_ >> centerLongitude_))
        throw WktParseException("Bad center coords");

    // parse radius
    try {
        radiusKm_ = std::stod(rad);
    } catch (...) {
        throw WktParseException("Bad radius");
    }
}

} // namespace geofence
