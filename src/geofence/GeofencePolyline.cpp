// src/geofence/GeofencePolyline.cpp
#include "GeofencePolyline.h"
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace geofence {

double GeofencePolyline::distanceToLine(double lat, double lon,
                                        double lat1, double lon1,
                                        double lat2, double lon2) const {
    double dx = lon2 - lon1;
    double dy = lat2 - lat1;
    double magSq = dx*dx + dy*dy;
    if (magSq == 0.0) {
        // Segmento degenerado a punto
        double dlon = lon - lon1;
        double dlat = lat - lat1;
        return std::sqrt(dlon*dlon + dlat*dlat) * kDegreeToKm;
    }
    double t = ((lon - lon1)*dx + (lat - lat1)*dy) / magSq;
    t = std::clamp(t, 0.0, 1.0);
    double projLon = lon1 + t*dx;
    double projLat = lat1 + t*dy;
    double dlon = lon - projLon;
    double dlat = lat - projLat;
    return std::sqrt(dlon*dlon + dlat*dlat) * kDegreeToKm;
}

bool GeofencePolyline::contains(double latitude, double longitude) const {
    for (size_t i = 1; i < coordinates_.size(); ++i) {
        const auto& a = coordinates_[i-1];
        const auto& b = coordinates_[i];
        double dist = distanceToLine(
            latitude, longitude,
            a.lat, a.lon,
            b.lat, b.lon
        );
        if (dist <= kDistanceThresholdKm) {
            return true;
        }
    }
    return false;
}

std::string GeofencePolyline::toWkt() const {
    std::ostringstream out;
    out << "LINESTRING (";
    for (size_t i = 0; i < coordinates_.size(); ++i) {
        if (i) out << ", ";
        out << coordinates_[i].lat << " " << coordinates_[i].lon;
    }
    out << ")";
    return out.str();
}

void GeofencePolyline::fromWkt(const std::string& wkt) {
    coordinates_.clear();
    const std::string prefix = "LINESTRING";
    if (wkt.rfind(prefix, 0) != 0) {
        throw WktParseException("Expected LINESTRING prefix");
    }
    auto lpar = wkt.find('(');
    auto rpar = wkt.find(')');
    if (lpar == std::string::npos || rpar == std::string::npos || rpar <= lpar+1) {
        throw WktParseException("Malformed parentheses in WKT");
    }
    std::string body = wkt.substr(lpar+1, rpar-lpar-1);
    std::istringstream ss(body);
    std::string token;
    while (std::getline(ss, token, ',')) {
        std::istringstream pair(token);
        double lat, lon;
        if (!(pair >> lat >> lon)) {
            throw WktParseException("Invalid coordinate pair: " + token);
        }
        Coordinate c{lat, lon};
        coordinates_.push_back(c);
    }
    if (coordinates_.size() < 2) {
        throw WktParseException("LINESTRING needs at least two points");
    }
}

} // namespace geofence
