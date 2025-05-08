// include/config/Config.cpp
#include "config/Config.h"
#include <cstdlib>
#include <regex>
#include <algorithm>

Config& Config::get() {
    static Config instance;
    return instance;
}

void Config::init(bool useEnvironmentVariables) {
    useEnv_ = useEnvironmentVariables;
}

void Config::set(const std::string& key, const std::string& value) {
    props_[key] = value;
}

void Config::setString(const ConfigKey<std::string>& key, const std::string& value) {
    set(key.key(), value);
}

bool Config::hasKey(const std::string& key) const {
    if (useEnv_) {
        auto env = toEnvName(key);
        if (std::getenv(env.c_str())) {
            return true;
        }
    }
    return props_.count(key) > 0;
}

template<typename T>
bool Config::hasKey(const ConfigKey<T>& key) const {
    return hasKey(key.key());
}

std::string Config::getString(const std::string& key, const std::string& defaultValue) const {
    if (useEnv_) {
        auto env = toEnvName(key);
        if (auto v = std::getenv(env.c_str()); v && *v) {
            return std::string(v);
        }
    }
    auto it = props_.find(key);
    if (it != props_.end()) {
        return it->second;
    }
    return defaultValue;
}

std::string Config::getString(const ConfigKey<std::string>& key) const {
    return getString(key.key(), key.defaultValue());
}

bool Config::getBool(const ConfigKey<bool>& key) const {
    auto s = getString(key.key(), key.defaultValue() ? "true" : "false");
    return s == "true" || s == "1";
}

int Config::getInt(const ConfigKey<int>& key) const {
    auto s = getString(key.key(), std::to_string(key.defaultValue()));
    return std::stoi(s);
}

long Config::getLong(const ConfigKey<long>& key) const {
    auto s = getString(key.key(), std::to_string(key.defaultValue()));
    return std::stol(s);
}

double Config::getDouble(const ConfigKey<double>& key) const {
    auto s = getString(key.key(), std::to_string(key.defaultValue()));
    return std::stod(s);
}

std::string Config::toEnvName(const std::string& key) {
    // replace '.' with '_'
    std::string r = std::regex_replace(key, std::regex{"\\."}, "_");
    // insert '_' before uppercase letters
    r = std::regex_replace(r, std::regex{"([A-Z])"}, "_$1");
    // uppercase all
    std::transform(r.begin(), r.end(), r.begin(), ::toupper);
    return r;
}

// Explicit instantiation for template
template bool Config::hasKey<int>(const ConfigKey<int>&) const;
template bool Config::hasKey<long>(const ConfigKey<long>&) const;
template bool Config::hasKey<bool>(const ConfigKey<bool>&) const;
template bool Config::hasKey<double>(const ConfigKey<double>&) const;
template bool Config::hasKey<std::string>(const ConfigKey<std::string>&) const;
