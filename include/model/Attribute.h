// include/model/Attribute.h
#pragma once

#include <string>
#include "model/BaseModel.h"

namespace model {

/// Attribute: describe una propiedad con expresión y prioridad.
class Attribute : public BaseModel {
public:
    // — Getters / Setters —

    /// Descripción legible de la attribute.
    const std::string& getDescription() const noexcept { return description_; }
    void setDescription(const std::string& desc) { description_ = desc; }

    /// Nombre interno de la attribute.
    const std::string& getAttribute() const noexcept { return attribute_; }
    void setAttribute(const std::string& attr) { attribute_ = attr; }

    /// Expresión asociada (por ejemplo, para cálculos dinámicos).
    const std::string& getExpression() const noexcept { return expression_; }
    void setExpression(const std::string& expr) { expression_ = expr; }

    /// Tipo de dato o categoría de la attribute.
    const std::string& getType() const noexcept { return type_; }
    void setType(const std::string& type) { type_ = type; }

    /// Prioridad de evaluación o despliegue.
    int getPriority() const noexcept { return priority_; }
    void setPriority(int p) noexcept { priority_ = p; }

private:
    std::string description_;
    std::string attribute_;
    std::string expression_;
    std::string type_;
    int         priority_{0};
};

} // namespace model
