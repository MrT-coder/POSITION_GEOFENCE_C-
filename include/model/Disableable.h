// include/model/Disableable.h
#pragma once

#include <chrono>
#include <optional>
#include <stdexcept>
#include <string>

namespace model {

/// Excepción que se lanza cuando un recurso está deshabilitado o ha expirado
class SecurityException : public std::runtime_error {
public:
    explicit SecurityException(const std::string& msg)
      : std::runtime_error(msg) {}
};

/// Interfaz Disableable: define habilitación y caducidad
class Disableable {
public:
    using TimePoint = std::chrono::system_clock::time_point;

    /// Indica si está deshabilitado
    virtual bool getDisabled() const = 0;
    /// Asigna estado de deshabilitado
    virtual void setDisabled(bool disabled) = 0;

    /// Fecha de expiración opcional
    virtual TimePoint getExpirationTime() const = 0;
    /// Asigna fecha de expiración
    virtual void setExpirationTime(TimePoint expiration) = 0;

    /// Comprueba y lanza SecurityException si está deshabilitado o expirado
    void checkDisabled() const {
        if (getDisabled()) {
            throw SecurityException(std::string("Resource is disabled"));
        }
        if (std::chrono::system_clock::now() > getExpirationTime()) {
            throw SecurityException(std::string("Resource has expired"));
        }
    }

    virtual ~Disableable() = default;
};

} // namespace model
