// include/config/Config.h
#pragma once

#include <string>
#include <unordered_map>
#include <optional>

// Template class representing a configuration key with a default value
template<typename T>
class ConfigKey {
public:
    ConfigKey(std::string key, T defaultValue)
        : key_(std::move(key)), defaultValue_(defaultValue) {}

    const std::string& key() const { return key_; }
    const T& defaultValue() const { return defaultValue_; }

private:
    std::string key_;
    T defaultValue_;
};

class Config {
public:
    // Get singleton instance
    static Config& get();

    // Initialize whether to use environment variables
    void init(bool useEnvironmentVariables);

    // Inject a property (e.g., from YAML)
    void set(const std::string& key, const std::string& value);

    // Testing helper
    void setString(const ConfigKey<std::string>& key, const std::string& value);

    // Check existence
    bool hasKey(const std::string& key) const;
    template<typename T>
    bool hasKey(const ConfigKey<T>& key) const;

    // Get value with default
    std::string getString(const std::string& key, const std::string& defaultValue = "") const;
    std::string getString(const ConfigKey<std::string>& key) const;

    bool        getBool   (const ConfigKey<bool>&    key) const;
    int         getInt    (const ConfigKey<int>&     key) const;
    long        getLong   (const ConfigKey<long>&    key) const;
    double      getDouble (const ConfigKey<double>&  key) const;

private:
    Config() = default;

    bool useEnv_{false};
    std::unordered_map<std::string,std::string> props_;

    static std::string toEnvName(const std::string& key);
};