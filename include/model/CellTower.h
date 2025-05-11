// include/model/CellTower.h
#pragma once

#include <string>
#include <optional>

namespace model {

/// Representa información de una torre celular
class CellTower {
public:
    /// Crea un CellTower con MCC, MNC, LAC y Cell ID
    static CellTower from(int mcc, int mnc, int lac, long cid);

    /// Crea un CellTower con MCC, MNC, LAC, Cell ID y RSSI
    static CellTower from(int mcc, int mnc, int lac, long cid, int rssi);

    /// Crea un CellTower a partir de configuración y LAC/CID
    template <typename Config>
    static CellTower fromLacCid(const Config& config, int lac, long cid);

    // Getters y setters
    const std::optional<std::string>& getRadioType() const noexcept { return radioType_; }
    void setRadioType(const std::string& radioType) { radioType_ = radioType; }

    long getCellId() const noexcept { return cellId_; }
    void setCellId(long cid) noexcept { cellId_ = cid; }

    int getLocationAreaCode() const noexcept { return locationAreaCode_; }
    void setLocationAreaCode(int lac) noexcept { locationAreaCode_ = lac; }

    int getMobileCountryCode() const noexcept { return mobileCountryCode_; }
    void setMobileCountryCode(int mcc) noexcept { mobileCountryCode_ = mcc; }

    int getMobileNetworkCode() const noexcept { return mobileNetworkCode_; }
    void setMobileNetworkCode(int mnc) noexcept { mobileNetworkCode_ = mnc; }

    const std::optional<int>& getSignalStrength() const noexcept { return signalStrength_; }
    void setSignalStrength(int rssi) noexcept {
        // En Java: si rssi > 0, se invierte el signo
        signalStrength_ = (rssi > 0 ? -rssi : rssi);
    }

    /// Divide un operador numérico MSC+MNC en MCC y MNC
    void setOperator(long op) {
        auto s = std::to_string(op);
        if (s.size() >= 4) {
            mobileCountryCode_ = std::stoi(s.substr(0, 3));
            mobileNetworkCode_ = std::stoi(s.substr(3));
        }
    }

    bool operator==(CellTower const& o) const noexcept {
        return radioType_       == o.radioType_ &&
               cellId_           == o.cellId_ &&
               locationAreaCode_ == o.locationAreaCode_ &&
               mobileCountryCode_== o.mobileCountryCode_ &&
               mobileNetworkCode_== o.mobileNetworkCode_ &&
               signalStrength_   == o.signalStrength_;
    }

private:
    std::optional<std::string> radioType_;
    long                       cellId_            = 0;
    int                        locationAreaCode_  = 0;
    int                        mobileCountryCode_ = 0;
    int                        mobileNetworkCode_ = 0;
    std::optional<int>         signalStrength_;
};

} // namespace model
