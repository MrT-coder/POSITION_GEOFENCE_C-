// include/protocol/PipelineBuilder.h
#pragma once

#include <memory>

namespace protocol {

/// Interfaz base para un handler en la cadena de procesamiento
class ChannelHandler {
public:
    virtual ~ChannelHandler() = default;

    /// Procesa datos de entrada (por ejemplo, bytes recibidos)
    virtual void handleRead(const std::vector<uint8_t>& data) = 0;

    /// Procesa datos de salida (por ejemplo, bytes a enviar)
    virtual void handleWrite(std::vector<uint8_t>& data) = 0;

    /// Notifica apertura de canal
    virtual void channelOpened() {}

    /// Notifica cierre de canal
    virtual void channelClosed() {}
};

/// Builder / ensamblador de pipelines de handlers
class PipelineBuilder {
public:
    virtual ~PipelineBuilder() = default;

    /// Añade un handler al final de la cadena
    ///
    /// @param handler   un puntero compartido al handler que deseas
    ///                  incluir en la secuencia de procesamiento.
    virtual void addLast(std::shared_ptr<ChannelHandler> handler) = 0;
};

} // namespace protocol
