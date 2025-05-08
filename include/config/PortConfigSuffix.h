// include/config/PortConfigSuffix.h
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "config/ConfigKey.h"
#include "config/KeyType.h"

namespace config {

class PortConfigSuffix {
public:
    // Constructor: recibe el sufijo de la clave y los tipos aplicables
    PortConfigSuffix(std::string keySuffix, std::vector<KeyType> types)
      : keySuffix_(std::move(keySuffix)), types_(std::move(types)) {}

    // Genera un ConfigKey<int> para el protocolo dado, usando el puerto por defecto si existe
    ConfigKey<int> withPrefix(const std::string& protocol) const {
        int defaultPort = 0;
        auto it = PORTS.find(protocol);
        if (it != PORTS.end()) {
            defaultPort = it->second;
        }
        return ConfigKey<int>(protocol + keySuffix_, types_, defaultPort);
    }

private:
    std::string keySuffix_;
    std::vector<KeyType> types_;

    // Mapa estático de puertos por protocolo
    static const std::unordered_map<std::string, int> PORTS;
};

} // namespace config


