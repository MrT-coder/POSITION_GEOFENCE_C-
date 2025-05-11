// include/model/UserRestrictions.h
#pragma once

namespace model {

/// Interfaz que define las restricciones de usuario
class UserRestrictions {
public:
    /// El servidor es de solo lectura
    virtual bool getReadonly() const = 0;
    /// Los dispositivos son de solo lectura
    virtual bool getDeviceReadonly() const = 0;
    /// ¿Limitar comandos?
    virtual bool getLimitCommands() const = 0;
    /// ¿Desactivar reportes?
    virtual bool getDisableReports() const = 0;
    /// ¿Correo fijo habilitado?
    virtual bool getFixedEmail() const = 0;

    virtual ~UserRestrictions() = default;
};

} // namespace model
