#pragma once

#include <string>
#include <set>
#include <vector>
#include <memory>

#include "Protocol.h"
#include "TrackerConnector.h"
#include "model/Command.h"
#include "helper/DataConverter.h"
#include "NetworkMessage.h"
#include "SmsManager.h"
#include "StringProtocolEncoder.h"

namespace protocol {

/// Versión C++ de tu BaseProtocol de Traccar.
/// Encapsula lógica de envío de comandos vía socket o SMS.
class BaseProtocol : public Protocol {
public:
    /// Construye el protocolo con un nombre (por ejemplo "osmand", "teltonika", ...)
    explicit BaseProtocol(std::string name);

    /// Nombre (lowercase) del protocolo
    std::string getName() const override { return name_; }

    /// Registrar un TrackerServer en este protocolo
    void addServer(std::shared_ptr<TrackerConnector> server);

    /// Registrar un TrackerClient en este protocolo
    void addClient(std::shared_ptr<TrackerConnector> client);

    /// Devuelve la lista de conectores (server + client)
    const std::vector<std::shared_ptr<TrackerConnector>>& getConnectorList() const override {
        return connectors_;
    }

    /// Establece qué comandos de datos (binarios) soporta
    void setSupportedDataCommands(std::initializer_list<std::string> cmds) {
        supportedDataCommands_.insert(cmds.begin(), cmds.end());
    }

    /// Establece qué comandos de texto (SMS) soporta
    void setSupportedTextCommands(std::initializer_list<std::string> cmds) {
        supportedTextCommands_.insert(cmds.begin(), cmds.end());
    }

    /// Obtiene la lista de comandos de datos soportados (incluye siempre "custom")
    std::vector<std::string> getSupportedDataCommands() const override;

    /// Obtiene la lista de comandos de texto soportados (incluye siempre "custom")
    std::vector<std::string> getSupportedTextCommands() const override;

    /// Envía un comando de datos a través del canal indicado (TCP/UDP)
    void sendDataCommand(Channel& channel,
                         const std::string& remoteAddress,
                         const model::Command& command) override;

    /// Inyecta un SmsManager para poder enviar comandos vía SMS
    void setSmsManager(SmsManager* mgr) { smsManager_ = mgr; }

    /// Inyecta el encoder de comandos de texto
    void setTextCommandEncoder(std::shared_ptr<StringProtocolEncoder> enc) {
        textCommandEncoder_ = std::move(enc);
    }

    /// Envía un comando por SMS
    void sendTextCommand(const std::string& destAddress,
                         const model::Command& command) override;

private:
    const std::string   name_;
    std::set<std::string> supportedDataCommands_;
    std::set<std::string> supportedTextCommands_;
    std::vector<std::shared_ptr<TrackerConnector>> connectors_;
    SmsManager*         smsManager_           = nullptr;
    std::shared_ptr<StringProtocolEncoder> textCommandEncoder_;
};

} // namespace protocol
