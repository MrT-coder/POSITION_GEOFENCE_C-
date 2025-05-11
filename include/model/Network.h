// include/model/Network.h
#pragma once

#include <string>
#include <vector>
#include <optional>
#include <algorithm>
#include "model/CellTower.h"
#include "model/WifiAccessPoint.h"

namespace model {

/// Representa información de red: torres celulares y puntos de acceso Wi-Fi
class Network {
public:
    using CellTowerList = std::vector<CellTower>;
    using WifiAccessPointList = std::vector<WifiAccessPoint>;

    Network() = default;

    explicit Network(const CellTowerList& cellTowers)
        : cellTowers_(cellTowers) {}

    explicit Network(const WifiAccessPointList& wifiAccessPoints)
        : wifiAccessPoints_(wifiAccessPoints) {}

    // — Getters / Setters —
    std::optional<int> getHomeMobileCountryCode() const noexcept {
        return homeMobileCountryCode_;
    }
    void setHomeMobileCountryCode(int mcc) {
        homeMobileCountryCode_ = mcc;
    }

    std::optional<int> getHomeMobileNetworkCode() const noexcept {
        return homeMobileNetworkCode_;
    }
    void setHomeMobileNetworkCode(int mnc) {
        homeMobileNetworkCode_ = mnc;
    }

    const std::string& getRadioType() const noexcept {
        return radioType_;
    }
    void setRadioType(const std::string& type) {
        radioType_ = type;
    }

    const std::string& getCarrier() const noexcept {
        return carrier_;
    }
    void setCarrier(const std::string& carrier) {
        carrier_ = carrier;
    }

    bool getConsiderIp() const noexcept {
        return considerIp_;
    }
    void setConsiderIp(bool considerIp) {
        considerIp_ = considerIp;
    }

    const CellTowerList& getCellTowers() const noexcept {
        return cellTowers_;
    }
    void setCellTowers(const CellTowerList& towers) {
        cellTowers_ = towers;
    }
    void addCellTower(const CellTower& tower) {
        cellTowers_.push_back(tower);
    }

    const WifiAccessPointList& getWifiAccessPoints() const noexcept {
        return wifiAccessPoints_;
    }
    void setWifiAccessPoints(const WifiAccessPointList& aps) {
        wifiAccessPoints_ = aps;
    }
    void addWifiAccessPoint(const WifiAccessPoint& ap) {
        wifiAccessPoints_.push_back(ap);
    }

    // — Comparación (equals/hashCode) —
    bool operator==(const Network& other) const noexcept {
        return homeMobileCountryCode_ == other.homeMobileCountryCode_
            && homeMobileNetworkCode_ == other.homeMobileNetworkCode_
            && radioType_          == other.radioType_
            && carrier_            == other.carrier_
            && considerIp_         == other.considerIp_
            && cellTowers_         == other.cellTowers_
            && wifiAccessPoints_   == other.wifiAccessPoints_;
    }

private:
    std::optional<int>        homeMobileCountryCode_;
    std::optional<int>        homeMobileNetworkCode_;
    std::string               radioType_        = "gsm";
    std::string               carrier_;
    bool                      considerIp_       = false;
    CellTowerList             cellTowers_;
    WifiAccessPointList       wifiAccessPoints_;
};

} // namespace model
