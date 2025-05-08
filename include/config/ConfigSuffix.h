// include/config/ConfigSuffix.h
#pragma once

#include <string>
#include <vector>
#include "config/ConfigKey.h"
#include "config/KeyType.h"

// Plantilla que representa un sufijo de configuración y genera ConfigKey<T> con un prefijo dado
template<typename T>
class ConfigSuffix {
public:
    ConfigSuffix(std::string keySuffix,
                 std::vector<KeyType> types = {},
                 T defaultValue = T{})
      : keySuffix_(std::move(keySuffix)),
        types_(std::move(types)),
        defaultValue_(std::move(defaultValue)) {}

    // Genera un ConfigKey<T> al anteponer el prefijo al sufijo
    ConfigKey<T> withPrefix(const std::string& prefix) const {
        return ConfigKey<T>(prefix + keySuffix_, types_, defaultValue_);
    }

private:
    std::string keySuffix_;
    std::vector<KeyType> types_;
    T defaultValue_;
};

// Alias para los tipos más comunes
using StringConfigSuffix  = ConfigSuffix<std::string>;
using BooleanConfigSuffix = ConfigSuffix<bool>;
using IntegerConfigSuffix = ConfigSuffix<int>;
using LongConfigSuffix    = ConfigSuffix<long>;
using DoubleConfigSuffix  = ConfigSuffix<double>;
