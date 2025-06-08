// include/protocol/NetworkMessage.h
#pragma once

#include <variant>
#include <vector>
#include <string>
#include <cstdint>

namespace protocol {

/// NetworkMessage: encapsula un mensaje de red con su payload y la dirección remota.
class NetworkMessage {
public:
    /// Un payload puede ser binario (vector de bytes) o texto (string)
    using Buffer = std::variant<std::vector<uint8_t>, std::string>;

    /// Constructor para payload binario
    NetworkMessage(std::vector<uint8_t> data, std::string remoteAddress)
        : payload_(std::move(data))
        , remoteAddress_(std::move(remoteAddress))
    {}

    /// Constructor para payload de texto
    NetworkMessage(std::string text, std::string remoteAddress)
        : payload_(std::move(text))
        , remoteAddress_(std::move(remoteAddress))
    {}

    /// Dirección remota (por ejemplo "192.168.0.1:4000")
    const std::string& remoteAddress() const noexcept {
        return remoteAddress_;
    }

    /// Acceso al payload (binario o texto)
    const Buffer& payload() const noexcept {
        return payload_;
    }

private:
    Buffer        payload_;
    std::string   remoteAddress_;
};

} // namespace protocol
