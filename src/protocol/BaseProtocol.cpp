#include "protocol/BaseProtocol.h"
#include "config/Keys.h"

using namespace protocol;
using model::Command;

BaseProtocol::BaseProtocol(std::string name)
    : name_(std::move(name))
{
    // vacía; los sets de comandos se llenan luego por setSupported…
}

std::vector<std::string> BaseProtocol::getSupportedDataCommands() const {
    // copia el set y añade siempre el comando "custom"
    auto cmds = supportedDataCommands_;
    cmds.insert(Command::TYPE_CUSTOM);
    return {cmds.begin(), cmds.end()};
}

std::vector<std::string> BaseProtocol::getSupportedTextCommands() const {
    auto cmds = supportedTextCommands_;
    cmds.insert(Command::TYPE_CUSTOM);
    return {cmds.begin(), cmds.end()};
}

void BaseProtocol::addServer(std::shared_ptr<TrackerConnector> server) {
    connectors_.push_back(std::move(server));
}

void BaseProtocol::addClient(std::shared_ptr<TrackerConnector> client) {
    connectors_.push_back(std::move(client));
}

void BaseProtocol::sendDataCommand(Channel& channel,
                                   const std::string& remoteAddress,
                                   const Command& command) {
    const auto& type = command.getType();

    if (supportedDataCommands_.count(type)) {
        // Mensaje binario o raw
        channel.write(NetworkMessage(command, remoteAddress));

    } else if (type == Command::TYPE_CUSTOM) {
        // Datos hex o texto
        std::string data = command.getString(Command::KEY_DATA);
        if (channel.hasHandler<StringEncoder>()) {
            // si hay un StringEncoder en el pipeline, enviamos texto crudo
            channel.write(NetworkMessage(
                data
                    .replace("\\r", "\r")
                    .replace("\\n", "\n"),
                remoteAddress));
        } else {
            // parseo hex → binario
            auto bytes = helper::DataConverter::parseHex(data);
            channel.write(NetworkMessage(bytes, remoteAddress));
        }

    } else {
        throw std::runtime_error(
            "Command " + type +
            " is not supported in protocol " + getName());
    }
}

void BaseProtocol::sendTextCommand(const std::string& destAddress,
                                   const Command& command) {
    if (!smsManager_) {
        throw std::runtime_error("SMS is not enabled");
    }

    const auto& type = command.getType();
    if (type == Command::TYPE_CUSTOM) {
        // envío directo
        smsManager_->sendMessage(
            destAddress,
            command.getString(Command::KEY_DATA),
            true);

    } else if (supportedTextCommands_.count(type)
               && textCommandEncoder_) {
        auto enc = textCommandEncoder_->encodeCommand(command);
        if (enc.has_value()) {
            smsManager_->sendMessage(destAddress, *enc, true);
        } else {
            throw std::runtime_error("Failed to encode command");
        }

    } else {
        throw std::runtime_error(
            "Command " + type +
            " is not supported in protocol " + getName());
    }
}
