#pragma once

#include <string>
#include <chrono>
#include <memory>
#include "protocol/PipelineBuilder.h"
#include "TrackerConnector.h"
#include "config/Config.h"

namespace protocol {

/// Adaptación C++ de tu BasePipelineFactory de Netty,
/// encargada de componer el pipeline de handlers para cada canal/sockect.
class BasePipelineFactory {
public:
    /// @param connector  objeto que indica si es UDP/TCP y manoje canal grupal
    /// @param cfg        clase de carga de configuración (keys, timeouts, forward, etc)
    /// @param protocol   nombre del protocolo (ej: "osmand", "teltonika", ...)
    BasePipelineFactory(TrackerConnector& connector,
                        config::Config& cfg,
                        const std::string& protocol);

    virtual ~BasePipelineFactory() = default;

    /// Inicializa el pipeline: invoca handlers en orden
    /// @param pipeline   builder donde se añaden los handlers
    void initPipeline(PipelineBuilder& pipeline);

protected:
    /// Añade framing, SSL, etc
    virtual void addTransportHandlers(PipelineBuilder& pipeline) = 0;

    /// Añade los handlers específicos de protocolo (decoder/encoder)
    virtual void addProtocolHandlers(PipelineBuilder& pipeline) = 0;

    TrackerConnector&      connector_;
    config::Config&        config_;
    std::string            protocol_;
    std::chrono::seconds   timeout_;
};

} // namespace protocol
