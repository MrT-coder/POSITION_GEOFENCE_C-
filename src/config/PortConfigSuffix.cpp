// src/config/PortConfigSuffix.cpp
#include "config/PortConfigSuffix.h"

namespace config {

const std::unordered_map<std::string,int> PortConfigSuffix::PORTS = {
    {"gps103",    5001}, {"tk103",      5002}, {"gl100",      5003},
    {"gl200",     5004}, {"t55",        5005}, {"xexun",      5006},
    {"totem",     5007}, {"enfora",     5008}, {"meiligao",   5009},
    {"trv",       5010}, {"suntech",    5011}, {"progress",   5012},
    {"h02",       5013}, {"jt600",      5014}, {"huabao",     5015},
    {"v680",      5016}, {"pt502",      5017}, {"tr20",       5018},
    {"navis",     5019}, {"meitrack",   5020}, {"skypatrol",  5021},
    {"gt02",      5022}, {"gt06",       5023}, {"megastek",   5024},
    {"navigil",   5025}, {"gpsgate",    5026}, {"teltonika",  5027},
    {"mta6",      5028}, {"tzone",      5029}, {"tlt2h",      5030},
    {"taip",      5031}, {"wondex",     5032}, {"cellocator", 5033},
    {"galileo",   5034}, {"ywt",        5035}, {"tk102",      5036},
    {"intellitrac",5037},{"gpsmta",     5038}, {"wialon",     5039},
    {"carscop",   5040}, {"apel",       5041}, {"manpower",   5042},
    {"globalsat", 5043}, {"atrack",     5044}, {"pt3000",     5045},
    // ... (continúa hasta cubrir todos los protocolos definidos en Java) ...
    {"osmand",     4999}, {"easytrack",  5056}, {"gpsmarker",  5057},
    {"khd",        5058}, {"piligrim",   5059}, {"stl060",     5060},
    {"cartrack",   5061}, {"minifinder", 5062}, {"haicom",     5063},
    {"eelink",     5064}, {"box",        5065}, {"freedom",    5066},
    {"telic",      5067}, {"trackbox",   5068}, {"visiontek",  5069},
    {"orion",      5070}, {"riti",       5071}, {"ulbotech",   5072},
    {"tramigo",    5073}, {"tr900",      5074}, {"ardi01",     5075},
    {"xt013",      5076}, {"autofon",    5077}, {"gosafe",     5078},
    {"tt8850",     5079}, {"bce",        5080}, {"xirgo",      5081},
    {"calamp",     5082}, {"mtx",        5083}, {"tytan",      5084},
    // Añade el resto de entradas aquí siguiendo el patrón Java original
};

} // namespace config
