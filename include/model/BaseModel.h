// include/model/BaseModel.h
#pragma once

namespace model {

/// BaseModel: clase base para todos los modelos de dominio, con un identificador único
class BaseModel {
public:
    /// Obtiene el identificador
    long getId() const noexcept { return id_; }

    /// Establece el identificador
    void setId(long id) noexcept { id_ = id; }

private:
    long id_{0};
};

} // namespace model
