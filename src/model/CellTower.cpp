// src/model/CellTower.cpp
#include "model/CellTower.h"

namespace model {

CellTower CellTower::from(int mcc, int mnc, int lac, long cid) {
    CellTower tower;
    tower.setMobileCountryCode(mcc);
    tower.setMobileNetworkCode(mnc);
    tower.setLocationAreaCode(lac);
    tower.setCellId(cid);
    return tower;
}

CellTower CellTower::from(int mcc, int mnc, int lac, long cid, int rssi) {
    CellTower tower = from(mcc, mnc, lac, cid);
    tower.setSignalStrength(rssi);
    return tower;
}

template <typename Config>
CellTower CellTower::fromLacCid(const Config& config, int lac, long cid) {
    return from(
        config.getInteger(/* Keys::GEOLOCATION_MCC */ "geolocation.mcc"),
        config.getInteger(/* Keys::GEOLOCATION_MNC */ "geolocation.mnc"),
        lac,
        cid
    );
}

// Instanciación explícita para tu clase Config (si la llamas Config)
// Si tu ConfigKey usa otro tipo de key, ajusta las llamadas:
template CellTower CellTower::fromLacCid<class Config>(const class Config&, int, long);

} // namespace model
