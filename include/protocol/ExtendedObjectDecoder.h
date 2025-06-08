// include/protocol/ExtendedObjectDecoder.h
#pragma once

#include <any>
#include <vector>
#include <memory>
#include <iostream>

#include "protocol/NetworkMessage.h"
#include "config/Config.h"
#include "handler/network/AcknowledgementHandler.h"
#include "helper/DataConverter.h"

namespace protocol {

/// Base class para decodificar objetos de red extendidos.
/// Gestiona ACK, almacenamiento de payload original y despacha el mensaje decodificado.
class ExtendedObjectDecoder {
public:
    explicit ExtendedObjectDecoder(config::Config& config)
        : config_(config) {
        init();
    }
    virtual ~ExtendedObjectDecoder() = default;

    /// Llama este método cuando llegue un NetworkMessage
    /// \param msg  mensaje recibido (mueve el buffer original dentro de él)
    void onMessage(NetworkMessage&& msg) {
        // 1) Envía EventReceived
        AcknowledgementHandler::sendEventReceived();

        // 2) Decodifica
        auto original = msg.payload();
        std::any decoded;
        try {
            decoded = decode(msg.remoteAddress(), original);
            onMessageEvent(msg.remoteAddress(), original, decoded);
        } catch (const std::exception& e) {
            std::cerr << "Decode error: " << e.what() << "\n";
            decoded.reset();
        }

        // 3) Si viene null, intenta handleEmptyMessage
        if (!decoded.has_value()) {
            decoded = handleEmptyMessage(msg.remoteAddress(), original);
        }

        // 4) Envía EventDecoded y despacha
        if (decoded.has_value()) {
            // colección
            if (decoded.type() == typeid(std::vector<std::any>)) {
                auto& coll = std::any_cast<std::vector<std::any>&>(decoded);
                AcknowledgementHandler::sendEventDecoded(coll);
                for (auto& item : coll) {
                    saveOriginal(item, original);
                    fireNext(item);
                }
            } else {
                std::vector<std::any> coll{decoded};
                AcknowledgementHandler::sendEventDecoded(coll);
                saveOriginal(decoded, original);
                fireNext(decoded);
            }
        } else {
            AcknowledgementHandler::sendEventDecoded({});
        }
    }

protected:
    config::Config& config_;

    /// Override para inicializar tras recibir Config
    virtual void init() {}

    /// Tu implementación debe devolver un objeto (Position, Event, etc.) o std::vector<std::any>
    virtual std::any decode(const std::string& remoteAddress,
                            const NetworkMessage::Buffer& msg) = 0;

    /// Se llama tras decode(), antes de dispatch. Puedes registrar métricas, logs…
    virtual void onMessageEvent(const std::string& remoteAddress,
                                const NetworkMessage::Buffer& original,
                                const std::any& decoded) {}

    /// Si decode() devuelve vacío, se puede generar un valor “vacío”
    virtual std::any handleEmptyMessage(const std::string& remoteAddress,
                                        const NetworkMessage::Buffer& original) {
        return {};
    }

private:
    /// Almacena en el objeto decodificado su representación hex original
    void saveOriginal(std::any& decoded,
                      const NetworkMessage::Buffer& original) {
        if (config_.getBoolean(config::Keys::DATABASE_SAVE_ORIGINAL) &&
            decoded.type() == typeid(model::Position)) {
            auto& pos = std::any_cast<model::Position&>(decoded);
            if (std::holds_alternative<std::vector<uint8_t>>(original)) {
                auto& buf = std::get<std::vector<uint8_t>>(original);
                pos.set(model::Position::KEY_ORIGINAL,
                        helper::DataConverter::toHex(buf));
            } else {
                auto& str = std::get<std::string>(original);
                pos.set(model::Position::KEY_ORIGINAL,
                        helper::DataConverter::toHex(
                            std::vector<uint8_t>(str.begin(), str.end())));
            }
        }
    }

    /// Aquí invocarías al siguiente handler de tu pipeline
    void fireNext(const std::any& decoded) {
        // p.ej. channel->nextHandler(decoded);
    }
};

} // namespace protocol
