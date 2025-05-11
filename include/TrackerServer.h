// include/protocol/TrackerServer.h
#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <vector>

#include "config/Config.h"
#include "config/Keys.h"
#include "protocol/TrackerConnector.h"
#include "protocol/BasePipelineFactory.h"
#include "protocol/EventLoopGroupFactory.h"
#include "protocol/PipelineBuilder.h"

/// Emula exactamente tu TrackerServer Java: levanta TCP o UDP según el flag,
/// aplica SSL si está configurado, y delega en BasePipelineFactory.
class TrackerServer : public protocol::TrackerConnector,
                      public std::enable_shared_from_this<TrackerServer> {
public:
    TrackerServer(config::Config& config,
                  const std::string& protocol,
                  bool datagram)
      : io_context_(protocol::EventLoopGroupFactory::getIoContext()),
        datagram_(datagram),
        secure_(config.getBoolean(Keys::PROTOCOL_SSL.withPrefix(protocol))),
        address_(config.getString(Keys::PROTOCOL_ADDRESS.withPrefix(protocol))),
        port_(config.getInteger(Keys::PROTOCOL_PORT.withPrefix(protocol))),
        tcp_acceptor_(io_context_),
        pipeline_factory_(std::make_unique<protocol::BasePipelineFactory>(this, config, protocol))
    {
        if (datagram_) {
            udp_socket_ = std::make_shared<boost::asio::ip::udp::socket>(
                io_context_,
                boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port_));
        } else {
            using tcp = boost::asio::ip::tcp;
            tcp_acceptor_.open(tcp::v4());
            tcp_acceptor_.set_option(tcp::acceptor::reuse_address(true));
            tcp_acceptor_.bind({ address_.empty()
                                    ? boost::asio::ip::address_v4::any()
                                    : boost::asio::ip::make_address(address_),
                                static_cast<unsigned short>(port_) });
            tcp_acceptor_.listen();
        }
    }

    void start() override {
        if (datagram_) {
            doReceive();
        } else {
            doAccept();
        }
    }

    void stop() override {
        // Cierra los sockets y limpia el grupo
        if (datagram_) {
            udp_socket_->close();
        } else {
            tcp_acceptor_.close();
        }
        channel_group_.clear();
    }

    bool isDatagram() const override { return datagram_; }
    bool isSecure()   const override { return secure_;   }

    const std::string& getAddress() const { return address_; }
    int                 getPort()    const { return port_;    }

protected:
    /// Subclases deben implementar aquí los handlers de protocolo
    virtual void addProtocolHandlers(protocol::PipelineBuilder& pipeline,
                                     config::Config& config) = 0;

private:
    // Aceptación TCP en bucle
    void doAccept() {
        auto sock = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
        tcp_acceptor_.async_accept(*sock,
            [this, sock](auto ec) {
                if (!ec) {
                    // Monta el pipeline (framing, SSL, handlers...)
                    protocol::PipelineBuilder pb(sock);
                    pipeline_factory_->addTransportHandlers(pb);
                    pipeline_factory_->addProtocolHandlers(pb);
                    channel_group_.push_back(sock);
                }
                doAccept();
            });
    }

    // Recepción UDP en bucle
    void doReceive() {
        auto buf      = std::make_shared<std::vector<uint8_t>>(2048);
        auto endpoint = std::make_shared<boost::asio::ip::udp::endpoint>();
        udp_socket_->async_receive_from(
            boost::asio::buffer(*buf), *endpoint,
            [this, buf, endpoint](auto ec, std::size_t len) {
                if (!ec && len > sizeof(uint32_t)) {
                    // Empaqueta en un contexto UDP y monta el pipeline
                    struct UdpContext {
                        boost::asio::ip::udp::socket* socket;
                        boost::asio::ip::udp::endpoint  remote;
                        uint8_t*                       data;
                        std::size_t                    length;
                    } ctx{ udp_socket_.get(), *endpoint, buf->data(), len };

                    protocol::PipelineBuilder pb(ctx);
                    pipeline_factory_->addTransportHandlers(pb);
                    pipeline_factory_->addProtocolHandlers(pb);
                    // Nota: no almacenamos ctx en channel_group_, sólo mantenemos buf/endpoint vivos
                }
                doReceive();
            });
    }

    boost::asio::io_context&                                       io_context_;
    bool                                                           datagram_;
    bool                                                           secure_;
    std::string                                                    address_;
    int                                                            port_;
    boost::asio::ip::tcp::acceptor                                 tcp_acceptor_;
    std::shared_ptr<boost::asio::ip::udp::socket>                  udp_socket_;
    std::vector<std::shared_ptr<void>>                             channel_group_;   // mantiene vivos sockets
    std::unique_ptr<protocol::BasePipelineFactory>                 pipeline_factory_;
};
