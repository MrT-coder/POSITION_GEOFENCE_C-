#include "geofence/GeofencePolygon.h"
#include <cmath>

namespace geofence {

double GeofencePolygon::calculateArea() const {
    double area = 0.0;
    size_t n = coordinates_.size();
    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;
        const auto& ci = coordinates_[i];
        const auto& cj = coordinates_[j];
        area += ci.lon * cj.lat;
        area -= cj.lon * ci.lat;
    }
    return std::abs(area) * 0.5;
}

bool GeofencePolygon::containsPoint(void* /*config*/, void* /*geofence*/, double latitude, double longitude) const {
    bool inside = false;
    size_t n = coordinates_.size();
    for (size_t i = 0, j = n - 1; i < n; j = i++) {
        const auto& ci = coordinates_[i];
        const auto& cj = coordinates_[j];
        bool intersect = ((ci.lat > latitude) != (cj.lat > latitude)) &&
            (longitude < (cj.lon - ci.lon) * (latitude - ci.lat) / (cj.lat - ci.lat) + ci.lon);
        if (intersect) inside = !inside;
    }
    return inside;
}

std::string GeofencePolygon::toWkt() const {
    std::ostringstream oss;
    oss << "POLYGON ((";
    for (size_t i = 0; i < coordinates_.size(); ++i) {
        const auto& c = coordinates_[i];
        oss << c.lat << " " << c.lon;
        if (i + 1 < coordinates_.size()) oss << ", ";
    }
    oss << "))";
    return oss.str();
}

void GeofencePolygon::fromWkt(const std::string& wkt) {
    coordinates_.clear();
    const std::string prefix = "POLYGON ((";
    const std::string suffix = "))";
    if (wkt.rfind(prefix, 0) != 0 || wkt.size() < prefix.size() + suffix.size()) {
        throw std::invalid_argument("Mismatch geometry type");
    }
    // extraer el contenido interior
    std::string content = wkt.substr(prefix.size(), wkt.size() - prefix.size() - suffix.size());
    if (content.empty()) {
        throw std::invalid_argument("No content");
    }
    // split por coma
    size_t start = 0;
    while (start < content.size()) {
        auto comma = content.find(',', start);
        std::string token = (comma == std::string::npos)
            ? content.substr(start)
            : content.substr(start, comma - start);
        std::istringstream iss(token);
        double lat, lon;
        if (!(iss >> lat >> lon)) {
            throw std::invalid_argument("Invalid coordinate: " + token);
        }
        geofence::GeofenceGeometry::Coordinate c;
        c.lat=lat;
        c.lon=lon;
        coordinates_.push_back(c);
        if (comma == std::string::npos) break;
        start = comma + 1;
    }
    if (coordinates_.size() < 3) {
        throw std::invalid_argument("Not valid content: need at least 3 points");
    }
}

} // namespace geofence
