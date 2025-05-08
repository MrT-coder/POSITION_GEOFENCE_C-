// include/model/GroupedModel.h
#pragma once

#include "model/ExtendedModel.h"

namespace model {

/// GroupedModel: extiende ExtendedModel añadiendo un identificador de grupo
class GroupedModel : public ExtendedModel {
public:
    /// Obtiene el ID de grupo
    long getGroupId() const noexcept { return groupId_; }
    /// Asigna el ID de grupo
    void setGroupId(long id) noexcept { groupId_ = id; }

private:
    long groupId_{0};
};

} // namespace model
