// include/model/Message.h
#pragma once

#include "model/ExtendedModel.h"
#include <string>

namespace model {

/// Message: extiende ExtendedModel añadiendo deviceId y tipo de mensaje
class Message : public ExtendedModel {
public:
    /// Obtiene el ID del dispositivo asociado a este mensaje
    long getDeviceId() const noexcept { return deviceId_; }
    /// Asigna el ID del dispositivo asociado
    void setDeviceId(long id) noexcept { deviceId_ = id; }

    /// Obtiene el tipo de mensaje
    const std::string& getType() const noexcept { return type_; }
    /// Asigna el tipo de mensaje
    void setType(const std::string& t) { type_ = t; }

private:
    long deviceId_{0};
    std::string type_;
};

} // namespace model