// include/model/ExtendedModel.h
#pragma once

#include <unordered_map>
#include <any>
#include <string>
#include <optional>
#include <typeinfo>
#include <algorithm>
#include <sstream>
#include "model/BaseModel.h"

namespace model {

class ExtendedModel : public BaseModel {
public:
    using AttributeMap = std::unordered_map<std::string, std::any>;

    // Comprueba si existe el atributo
    bool hasAttribute(const std::string& key) const noexcept {
        return attributes_.count(key) > 0;
    }

    // Acceso directo al mapa de atributos
    const AttributeMap& getAttributes() const noexcept {
        return attributes_;
    }

    // Reemplaza el mapa de atributos
    void setAttributes(const AttributeMap& attrs) {
        attributes_ = attrs;
    }

    // Setters para distintos tipos (ignoran valores nulos/vacíos)
    void set(const std::string& key, bool value) {
        attributes_[key] = value;
    }
    void set(const std::string& key, unsigned char value) {
        attributes_[key] = static_cast<int>(value);
    }
    void set(const std::string& key, short value) {
        attributes_[key] = static_cast<int>(value);
    }
    void set(const std::string& key, int value) {
        attributes_[key] = value;
    }
    void set(const std::string& key, long value) {
        attributes_[key] = value;
    }
    void set(const std::string& key, float value) {
        attributes_[key] = static_cast<double>(value);
    }
    void set(const std::string& key, double value) {
        attributes_[key] = value;
    }
    void set(const std::string& key, const std::string& value) {
        if (!value.empty()) {
            attributes_[key] = value;
        }
    }

    // Agrega un par clave/valor si el valor existe
    void add(const std::pair<std::string, std::any>& entry) {
        if (entry.second.has_value()) {
            attributes_[entry.first] = entry.second;
        }
    }

    // Lectores con valor por defecto
    std::string getString(const std::string& key, const std::string& defaultValue) const {
        auto it = attributes_.find(key);
        return it == attributes_.end() ? defaultValue
            : parseAsString(it->second, defaultValue);
    }
    std::string getString(const std::string& key) const {
        return getString(key, {});
    }

    double getDouble(const std::string& key) const {
        auto it = attributes_.find(key);
        return it == attributes_.end() ? 0.0
            : parseAsDouble(it->second, 0.0);
    }

    bool getBoolean(const std::string& key) const {
        auto it = attributes_.find(key);
        return it == attributes_.end() ? false
            : parseAsBoolean(it->second, false);
    }

    int getInteger(const std::string& key) const {
        auto it = attributes_.find(key);
        return it == attributes_.end() ? 0
            : parseAsInteger(it->second, 0);
    }

    long getLong(const std::string& key) const {
        auto it = attributes_.find(key);
        return it == attributes_.end() ? 0L
            : parseAsLong(it->second, 0L);
    }

    // Eliminación de atributos
    std::any removeAttribute(const std::string& key) {
        auto it = attributes_.find(key);
        if (it == attributes_.end()) return {};
        std::any val = it->second;
        attributes_.erase(it);
        return val;
    }

    std::optional<std::string> removeString(const std::string& key) {
        std::any val = removeAttribute(key);
        if (!val.has_value()) return std::nullopt;
        return parseAsString(val, {});
    }

    std::optional<double> removeDouble(const std::string& key) {
        std::any val = removeAttribute(key);
        if (!val.has_value()) return std::nullopt;
        return parseAsDouble(val, 0.0);
    }

    std::optional<bool> removeBoolean(const std::string& key) {
        std::any val = removeAttribute(key);
        if (!val.has_value()) return std::nullopt;
        return parseAsBoolean(val, false);
    }

    std::optional<int> removeInteger(const std::string& key) {
        std::any val = removeAttribute(key);
        if (!val.has_value()) return std::nullopt;
        return parseAsInteger(val, 0);
    }

    std::optional<long> removeLong(const std::string& key) {
        std::any val = removeAttribute(key);
        if (!val.has_value()) return std::nullopt;
        return parseAsLong(val, 0L);
    }

private:
    AttributeMap attributes_;

    // Parse helpers
    static std::string parseAsString(const std::any& v, const std::string& def) {
        if (!v.has_value()) return def;
        if (v.type() == typeid(std::string)) {
            return std::any_cast<std::string>(v);
        }
        if (v.type() == typeid(const char*)) {
            return std::string(std::any_cast<const char*>(v));
        }
        if (v.type() == typeid(bool)) {
            return std::any_cast<bool>(v) ? "true" : "false";
        }
        try {
            if (v.type() == typeid(int)) {
                return std::to_string(std::any_cast<int>(v));
            }
            if (v.type() == typeid(long)) {
                return std::to_string(std::any_cast<long>(v));
            }
            if (v.type() == typeid(double)) {
                return std::to_string(std::any_cast<double>(v));
            }
        } catch (...) {}
        return def;
    }

    static double parseAsDouble(const std::any& v, double def) {
        if (!v.has_value()) return def;
        try {
            if (v.type() == typeid(double)) {
                return std::any_cast<double>(v);
            }
            if (v.type() == typeid(float)) {
                return static_cast<double>(std::any_cast<float>(v));
            }
            if (v.type() == typeid(int)) {
                return static_cast<double>(std::any_cast<int>(v));
            }
            if (v.type() == typeid(long)) {
                return static_cast<double>(std::any_cast<long>(v));
            }
            if (v.type() == typeid(std::string)) {
                return std::stod(std::any_cast<std::string>(v));
            }
        } catch (...) {}
        return def;
    }

    static bool parseAsBoolean(const std::any& v, bool def) {
        if (!v.has_value()) return def;
        try {
            if (v.type() == typeid(bool)) {
                return std::any_cast<bool>(v);
            }
            if (v.type() == typeid(int)) {
                return std::any_cast<int>(v) != 0;
            }
            if (v.type() == typeid(long)) {
                return std::any_cast<long>(v) != 0L;
            }
            if (v.type() == typeid(std::string)) {
                auto s = std::any_cast<std::string>(v);
                std::transform(s.begin(), s.end(), s.begin(), ::tolower);
                return s == "true" || s == "1";
            }
        } catch (...) {}
        return def;
    }

    static int parseAsInteger(const std::any& v, int def) {
        if (!v.has_value()) return def;
        try {
            if (v.type() == typeid(int)) {
                return std::any_cast<int>(v);
            }
            if (v.type() == typeid(long)) {
                return static_cast<int>(std::any_cast<long>(v));
            }
            if (v.type() == typeid(double)) {
                return static_cast<int>(std::any_cast<double>(v));
            }
            if (v.type() == typeid(std::string)) {
                return std::stoi(std::any_cast<std::string>(v));
            }
        } catch (...) {}
        return def;
    }

    static long parseAsLong(const std::any& v, long def) {
        if (!v.has_value()) return def;
        try {
            if (v.type() == typeid(long)) {
                return std::any_cast<long>(v);
            }
            if (v.type() == typeid(int)) {
                return static_cast<long>(std::any_cast<int>(v));
            }
            if (v.type() == typeid(double)) {
                return static_cast<long>(std::any_cast<double>(v));
            }
            if (v.type() == typeid(std::string)) {
                return std::stol(std::any_cast<std::string>(v));
            }
        } catch (...) {}
        return def;
    }
};

} // namespace model
