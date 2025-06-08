#include "protocol/BasePipelineFactory.h"
#include "handler/network/OpenChannelHandler.h"
#include "handler/network/NetworkForwarderHandler.h"
#include "handler/network/NetworkMessageHandler.h"
#include "handler/network/StandardLoggingHandler.h"
#include "handler/network/AcknowledgementHandler.h"
#include "handler/network/RemoteAddressHandler.h"
#include "handler/network/ProcessingHandler.h"
#include "handler/network/MainEventHandler.h"
#include "config/Keys.h"

using namespace std::chrono;
using namespace protocol;

BasePipelineFactory::BasePipelineFactory(TrackerConnector& connector,
                                         config::Config& cfg,
                                         const std::string& protocol)
    : connector_(connector),
      config_(cfg),
      protocol_(protocol)
{
    // timeout = protocol.timeout si >0, sino server.timeout
    int t = config_.getInteger(config::Keys::PROTOCOL_TIMEOUT.withPrefix(protocol_));
    if (t == 0) {
        t = config_.getInteger(config::Keys::SERVER_TIMEOUT);
    }
    timeout_ = seconds(t);
}

void BasePipelineFactory::initPipeline(PipelineBuilder& pipeline) {
    // 1) Transporte puro (framing, SSL…)
    addTransportHandlers(pipeline);

    // 2) Idle timeout (solo TCP y si timeout_ > 0)
    if (!connector_.isDatagram() && timeout_.count() > 0) {
        pipeline.addLast(std::make_shared<RemoteAddressHandler>()); // placeholder IdleTimeoutHandler
        // En realidad aquí implementarías tu propia clase IdleTimeoutHandler
        // que use asio::steady_timer para cerrar el socket tras timeout_ sin lecturas.
    }

    // 3) Canal abierto / forwarder / logging / mensaje bruto
    pipeline.addLast(std::make_shared<OpenChannelHandler>(connector_));
    if (config_.hasKey(config::Keys::SERVER_FORWARD)) {
        int port = config_.getInteger(config::Keys::PROTOCOL_PORT.withPrefix(protocol_));
        pipeline.addLast(std::make_shared<NetworkForwarderHandler>(port));
    }
    pipeline.addLast(std::make_shared<NetworkMessageHandler>());
    pipeline.addLast(std::make_shared<StandardLoggingHandler>(protocol_));

    // 4) ACK si toca
    if (!connector_.isDatagram()
        && !config_.getBoolean(config::Keys::SERVER_INSTANT_ACKNOWLEDGEMENT)) {
        pipeline.addLast(std::make_shared<AcknowledgementHandler>());
    }

    // 5) Protocolo concreto (decoder/encoder)
    addProtocolHandlers(pipeline);

    // 6) Resto de la cadena de eventos
    pipeline.addLast(std::make_shared<RemoteAddressHandler>());
    pipeline.addLast(std::make_shared<ProcessingHandler>());
    pipeline.addLast(std::make_shared<MainEventHandler>());
}
