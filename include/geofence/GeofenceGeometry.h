// include/geofence/GeofenceGeometry.h
#pragma once

#include <string>
#include <stdexcept>

namespace geofence {

/// Excepción lanzada al parsear WKT inválido
class WktParseException : public std::runtime_error {
public:
    explicit WktParseException(const std::string& msg)
        : std::runtime_error("WKT parse error: " + msg) {}
};

/// Clase base para toda geometría de geocerca
class GeofenceGeometry {
public:
    virtual ~GeofenceGeometry() = default;

    /// Determina si el punto (latitude, longitude) está dentro de la geometría
    virtual bool contains(double latitude, double longitude) const = 0;

    /// Calcula el área de la geometría
    virtual double area() const = 0;

    /// Devuelve la representación WKT de la geometría
    virtual std::string toWkt() const = 0;

    /// Parsea una cadena WKT para inicializar la geometría. Lanza WktParseException si falla.
    virtual void fromWkt(const std::string& wkt) = 0;

    /// Representa una coordenada (latitud, longitud)
    struct Coordinate {
        double lat{0.0};
        double lon{0.0};
    };
};

} // namespace geofence
