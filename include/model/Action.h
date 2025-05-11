// include/model/Action.h
#pragma once

#include <string>
#include <chrono>
#include "model/ExtendedModel.h"

namespace model {

/// Action: representa una acción realizada por un usuario sobre un objeto,
/// con marca de tiempo y metadatos.
class Action : public ExtendedModel {
public:
    using TimePoint = std::chrono::system_clock::time_point;

    /// Constructor: inicializa actionTime_ al momento actual.
    Action()
        : actionTime_(std::chrono::system_clock::now())
    {}

    // — Getters / Setters —

    /// Tiempo en que ocurrió la acción.
    TimePoint getActionTime() const noexcept { return actionTime_; }
    void setActionTime(TimePoint t) { actionTime_ = t; }

    /// Dirección o ubicación asociada a la acción.
    const std::string& getAddress() const noexcept { return address_; }
    void setAddress(const std::string& addr) { address_ = addr; }

    /// ID del usuario que realizó la acción.
    long getUserId() const noexcept { return userId_; }
    void setUserId(long id) noexcept { userId_ = id; }

    /// Tipo de acción (por ejemplo, "create", "update", "delete", etc.).
    const std::string& getActionType() const noexcept { return actionType_; }
    void setActionType(const std::string& type) { actionType_ = type; }

    /// Tipo de objeto sobre el que se realizó la acción (por ejemplo, "Device", "Position", etc.).
    const std::string& getObjectType() const noexcept { return objectType_; }
    void setObjectType(const std::string& objType) { objectType_ = objType; }

    /// ID del objeto afectado por la acción.
    long getObjectId() const noexcept { return objectId_; }
    void setObjectId(long id) noexcept { objectId_ = id; }

private:
    TimePoint   actionTime_;
    std::string address_;
    long        userId_{0};
    std::string actionType_;
    std::string objectType_;
    long        objectId_{0};
};

} // namespace model
