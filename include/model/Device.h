// include/model/Device.h
#pragma once

#include <string>
#include <chrono>
#include <stdexcept>
#include "model/GroupedModel.h"
#include "model/Disableable.h"
#include "model/Schedulable.h"

namespace model {

class Device : public GroupedModel, public Disableable, public Schedulable {
public:
    using TimePoint = std::chrono::system_clock::time_point;

    // Status constants
    static inline const std::string STATUS_UNKNOWN = "unknown";
    static inline const std::string STATUS_ONLINE  = "online";
    static inline const std::string STATUS_OFFLINE = "offline";

    // Calendar ID (from Schedulable)
    long getCalendarId() const override { return calendarId_; }
    void setCalendarId(long id) override { calendarId_ = id; }

    // Name
    const std::string& getName() const noexcept { return name_; }
    void setName(const std::string& n) { name_ = n; }

    // Unique ID with validation
    const std::string& getUniqueId() const noexcept { return uniqueId_; }
    void setUniqueId(const std::string& uid) {
        if (uid.find("..") != std::string::npos) {
            throw std::invalid_argument("Invalid unique id");
        }
        auto first = uid.find_first_not_of(" \t\n\r");
        auto last  = uid.find_last_not_of(" \t\n\r");
        uniqueId_ = (first == std::string::npos)
            ? std::string()
            : uid.substr(first, last - first + 1);
    }

    // Status with default offline
    const std::string& getStatus() const noexcept {
        return status_.empty() ? STATUS_OFFLINE : status_;
    }
    void setStatus(const std::string& s) {
        auto first = s.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) {
            status_.clear();
        } else {
            auto last = s.find_last_not_of(" \t\n\r");
            status_ = s.substr(first, last - first + 1);
        }
    }

    // Last update timestamp
    TimePoint getLastUpdate() const noexcept { return lastUpdate_; }
    void setLastUpdate(TimePoint t) { lastUpdate_ = t; }

    // Last known position ID
    long getPositionId() const noexcept { return positionId_; }
    void setPositionId(long id) { positionId_ = id; }

    // Phone
    const std::string& getPhone() const noexcept { return phone_; }
    void setPhone(const std::string& p) {
        auto first = p.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) {
            phone_.clear();
        } else {
            auto last = p.find_last_not_of(" \t\n\r");
            phone_ = p.substr(first, last - first + 1);
        }
    }

    // Model, Contact, Category
    const std::string& getModel() const noexcept { return model_; }
    void setModel(const std::string& m) { model_ = m; }

    const std::string& getContact() const noexcept { return contact_; }
    void setContact(const std::string& c) { contact_ = c; }

    const std::string& getCategory() const noexcept { return category_; }
    void setCategory(const std::string& c) { category_ = c; }

    // Disableable interface
    bool getDisabled() const override { return disabled_; }
    void setDisabled(bool d) override { disabled_ = d; }

    // Schedulable interface
    TimePoint getExpirationTime() const override { return expirationTime_; }
    void setExpirationTime(TimePoint t) override { expirationTime_ = t; }

    // Motion tracking fields (ignored in JSON)
    bool getMotionStreak() const noexcept { return motionStreak_; }
    void setMotionStreak(bool v) noexcept { motionStreak_ = v; }

    bool getMotionState() const noexcept { return motionState_; }
    void setMotionState(bool v) noexcept { motionState_ = v; }

    TimePoint getMotionTime() const noexcept { return motionTime_; }
    void setMotionTime(TimePoint t) { motionTime_ = t; }

    double getMotionDistance() const noexcept { return motionDistance_; }
    void setMotionDistance(double d) noexcept { motionDistance_ = d; }

    // Overspeed tracking fields
    bool getOverspeedState() const noexcept { return overspeedState_; }
    void setOverspeedState(bool v) noexcept { overspeedState_ = v; }

    TimePoint getOverspeedTime() const noexcept { return overspeedTime_; }
    void setOverspeedTime(TimePoint t) { overspeedTime_ = t; }

    long getOverspeedGeofenceId() const noexcept { return overspeedGeofenceId_; }
    void setOverspeedGeofenceId(long id) noexcept { overspeedGeofenceId_ = id; }

private:
    long calendarId_{};
    std::string name_;
    std::string uniqueId_;
    std::string status_;
    TimePoint lastUpdate_{};
    long positionId_{};
    std::string phone_;
    std::string model_;
    std::string contact_;
    std::string category_;
    bool disabled_{false};
    TimePoint expirationTime_{};
    bool motionStreak_{false};
    bool motionState_{false};
    TimePoint motionTime_{};
    double motionDistance_{0.0};
    bool overspeedState_{false};
    TimePoint overspeedTime_{};
    long overspeedGeofenceId_{};
};

} // namespace model
