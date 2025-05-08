#include "decoder.h"
#include <cstring>
std::vector<uint8_t> encode_message(const std::string& payload) {
    // tu protocolo aquí (ejemplo: prefijo de longitud)
    std::vector<uint8_t> buf;
    uint32_t len = payload.size();
    buf.insert(buf.end(), reinterpret_cast<uint8_t*>(&len),
               reinterpret_cast<uint8_t*>(&len) + sizeof(len));
    buf.insert(buf.end(), payload.begin(), payload.end());
    return buf;
}

std::string decode_message(const std::vector<uint8_t>& raw) {
    // asume primer uint32_t = tamaño
    if (raw.size() < 4) return {};
    uint32_t len;
    memcpy(&len, raw.data(), 4);
    return std::string(raw.begin() + 4, raw.begin() + 4 + len);
}
