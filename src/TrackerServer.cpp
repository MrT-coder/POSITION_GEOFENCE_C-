// src/protocol/TrackerServer.cpp
#include "TrackerServer.h"
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>

namespace protocol {

TrackerServer::TrackerServer(boost::asio::io_context& io_context,
                             const config::Config& config,
                             const std::string& protocol,
                             bool datagram)
    : io_context_(io_context),
      datagram_(datagram),
      secure_(config.getBoolean(config::Keys::PROTOCOL_SSL.withPrefix(protocol))),
      address_(config.getString(config::Keys::PROTOCOL_ADDRESS.withPrefix(protocol))),
      port_(static_cast<unsigned short>(
          config.getInteger(config::Keys::PROTOCOL_PORT.withPrefix(protocol)))),
      ssl_context_(boost::asio::ssl::context::sslv23),
      udp_socket_(io_context)
{
    if (secure_) {
        ssl_context_.set_options(
            boost::asio::ssl::context::default_workarounds |
            boost::asio::ssl::context::no_sslv2 |
            boost::asio::ssl::context::single_dh_use
        );
    }

    if (datagram_) {
        // UDP bind
        boost::asio::ip::udp::endpoint ep{
            boost::asio::ip::make_address(
                address_.empty() ? "0.0.0.0" : address_),
            port_
        };
        udp_socket_.open(ep.protocol());
        udp_socket_.bind(ep);
    } else {
        // TCP acceptor
        acceptor_ = std::make_unique<boost::asio::ip::tcp::acceptor>(io_context_);
        boost::asio::ip::tcp::endpoint ep{
            boost::asio::ip::make_address(
                address_.empty() ? "0.0.0.0" : address_),
            port_
        };
        acceptor_->open(ep.protocol());
        acceptor_->set_option(
            boost::asio::ip::tcp::acceptor::reuse_address(true));
        acceptor_->bind(ep);
        acceptor_->listen();
    }
}

TrackerServer::~TrackerServer() {
    stop();
}

void TrackerServer::start() {
    if (datagram_) {
        doReceive();
    } else {
        doAccept();
    }
}

void TrackerServer::stop() {
    if (acceptor_) {
        boost::system::error_code ec;
        acceptor_->close(ec);
    }
    {
        boost::system::error_code ec;
        udp_socket_.close(ec);
    }
    // Al detener io_context_, todos los handlers pendientes cancelarán
    io_context_.stop();
}

void TrackerServer::doAccept() {
    auto sock = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
    acceptor_->async_accept(*sock,
        [self = shared_from_this(), sock]
        (const boost::system::error_code& ec) {
            self->onAccept(ec, sock);
        });
}

void TrackerServer::onAccept(const boost::system::error_code& ec,
                             std::shared_ptr<boost::asio::ip::tcp::socket> sock)
{
    if (!ec) {
        if (secure_) {
            // SSL handshake
            auto ssl_sock =
              std::make_shared<
                boost::asio::ssl::stream<boost::asio::ip::tcp::socket>
              >(std::move(*sock), ssl_context_);
            ssl_sock->async_handshake(
                boost::asio::ssl::stream_base::server,
                [self = shared_from_this(), ssl_sock]
                (const boost::system::error_code& ec2) {
                  if (!ec2) {
                    self->addProtocolHandlers(ssl_sock);
                  }
                }
            );
            channels_.push_back(ssl_sock);
        } else {
            // Aquí “enmascaramos” como SSL-stream para unificar la llamada
            auto ssl_sock =
              std::make_shared<
                boost::asio::ssl::stream<boost::asio::ip::tcp::socket>
              >(std::move(*sock), ssl_context_);
            addProtocolHandlers(ssl_sock);
            channels_.push_back(ssl_sock);
        }
    }
    // Siempre rearmamos otro accept
    doAccept();
}

void TrackerServer::doReceive() {
    udp_socket_.async_receive_from(
        boost::asio::buffer(udp_buffer_), remote_endpoint_,
        [self = shared_from_this()]
        (const boost::system::error_code& ec, std::size_t bytes) {
            self->onReceive(ec, bytes);
        });
}

void TrackerServer::onReceive(const boost::system::error_code& ec,
                              std::size_t bytes)
{
    if (!ec && bytes > 0) {
        std::vector<uint8_t> data(
            udp_buffer_.data(),
            udp_buffer_.data() + bytes
        );
        handleDatagram(remote_endpoint_, data);
    }
    // Seguimos recibiendo
    doReceive();
}

} // namespace protocol
