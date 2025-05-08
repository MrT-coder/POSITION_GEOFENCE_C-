// include/config/ConfigKey.h
#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>
#include "config/KeyType.h"  // Enum con valores equivalentes a los de Java

// Plantilla que representa una clave de configuración con metadatos y valor por defecto.
template<typename T>
class ConfigKey {
public:
    // Constructor con clave, tipos y valor por defecto opcional
    ConfigKey(std::string key,
              std::vector<KeyType> types = {},
              T defaultValue = T{})
        : key_(std::move(key)),
          types_(std::move(types)),
          defaultValue_(std::move(defaultValue))
    {}

    // Obtener la clave (ej. "httpPort")
    const std::string& getKey() const noexcept {
        return key_;
    }

    // ¿Esta clave admite el tipo indicado? (equivale a hasType)
    bool hasType(KeyType type) const noexcept {
        return std::find(types_.begin(), types_.end(), type) != types_.end();
    }

    // Tipo de valor en tiempo de compilación
    using ValueType = T;

    // Valor por defecto (puede ser T{} si no se especifica)
    const T& getDefaultValue() const noexcept {
        return defaultValue_;
    }

private:
    std::string key_;
    std::vector<KeyType> types_;
    T defaultValue_;
};

// Tipos especializados para facilitar la creación (opcional)
using StringConfigKey  = ConfigKey<std::string>;
using BooleanConfigKey = ConfigKey<bool>;
using IntegerConfigKey = ConfigKey<int>;
using LongConfigKey    = ConfigKey<long>;
using DoubleConfigKey  = ConfigKey<double>;
