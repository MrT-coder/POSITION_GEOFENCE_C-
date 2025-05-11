#pragma once

#include <string>
#include <optional>

namespace model {

/// Representation of a Wi-Fi access point detected by the device
class WifiAccessPoint {
public:
    /// Factory: create from MAC and signal strength
    static WifiAccessPoint from(const std::string& macAddress, int signalStrength) {
        WifiAccessPoint wap;
        wap.setMacAddress(macAddress);
        wap.setSignalStrength(signalStrength);
        return wap;
    }
    /// Factory: create from MAC, signal strength and channel
    static WifiAccessPoint from(const std::string& macAddress, int signalStrength, int channel) {
        WifiAccessPoint wap = from(macAddress, signalStrength);
        wap.setChannel(channel);
        return wap;
    }

    /// Get the MAC address (e.g. "00:11:22:33:44:55")
    const std::string& getMacAddress() const noexcept {
        return macAddress_;
    }
    /// Set the MAC address
    void setMacAddress(const std::string& mac) {
        macAddress_ = mac;
    }

    /// Get signal strength in dBm (negative values are typical)
    int getSignalStrength() const noexcept {
        return signalStrength_;
    }
    /// Set signal strength; positive inputs are converted to negative
    void setSignalStrength(int strength) {
        signalStrength_ = strength > 0 ? -strength : strength;
    }

    /// Get channel (if known)
    std::optional<int> getChannel() const noexcept {
        return channel_;
    }
    /// Set channel number
    void setChannel(int channel) {
        channel_ = channel;
    }

    /// Compare two WifiAccessPoint objects for equality
    bool operator==(const WifiAccessPoint& other) const noexcept {
        return macAddress_ == other.macAddress_
            && signalStrength_ == other.signalStrength_
            && channel_ == other.channel_;
    }
    bool operator!=(const WifiAccessPoint& other) const noexcept {
        return !(*this == other);
    }

private:
    std::string macAddress_;
    int signalStrength_{0};
    std::optional<int> channel_;
};

} // namespace model
