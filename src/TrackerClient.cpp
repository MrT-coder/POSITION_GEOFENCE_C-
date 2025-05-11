// src/TrackerClient.cpp
#include "TrackerClient.h"
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include "config/Keys.h"

namespace protocol {

TrackerClient::TrackerClient(boost::asio::io_context& io_context,
                             const config::Config& config,
                             const std::string& protocol)
    : io_context_(io_context),
      ssl_context_(boost::asio::ssl::context::sslv23_client),
      resolver_(std::make_unique<tcp::resolver>(io_context_)),
      retry_timer_(io_context_),
      secure_(config.getBoolean(config::Keys::PROTOCOL_SSL.withPrefix(protocol))),
      host_(config.getString(config::Keys::PROTOCOL_ADDRESS.withPrefix(protocol))),
      port_(static_cast<unsigned short>(
          config.getInteger(config::Keys::PROTOCOL_PORT.withPrefix(protocol),
                            secure_ ? 443 : 80))),
      interval_(std::chrono::seconds(
          config.getLong(config::Keys::PROTOCOL_INTERVAL.withPrefix(protocol)))),
      devices_([&]{
          auto s = config.getString(config::Keys::PROTOCOL_DEVICES.withPrefix(protocol));
          std::vector<std::string> v;
          boost::split(v, s, boost::is_any_of(", "));
          return v;
      }())
{
    // Opciones SSL 
    if (secure_) {
        ssl_context_.set_default_verify_paths();
        ssl_context_.set_verify_mode(
            boost::asio::ssl::verify_none);
    }
}

TrackerClient::~TrackerClient() {
    stop();
}

void TrackerClient::start() {
    stopped_ = false;
    doConnect();
}

void TrackerClient::stop() {
    stopped_ = true;
    boost::system::error_code ec;
    if (socket_) socket_->lowest_layer().close(ec);
    retry_timer_.cancel(ec);
}

void TrackerClient::doConnect() {
    if (stopped_) return;

    // Resolver DNS
    resolver_->async_resolve(host_, std::to_string(port_),
      [self = shared_from_this()](auto ec, auto results) {
        if (ec) {
            // error de resolución: schedule retry
            self->retry_timer_.expires_after(self->interval_);
            self->retry_timer_.async_wait(
              [self](auto){ self->doConnect(); });
            return;
        }
        // crear socket SSL
        self->socket_ =
          std::make_shared<ssl_socket_t>(self->io_context_, self->ssl_context_);
        // conectar TCP
        boost::asio::async_connect(
          self->socket_->lowest_layer(),
          results,
          [self](auto ec2, auto) {
            if (ec2) {
              // fallo de conexión: reintentar tras intervalo
              self->retry_timer_.expires_after(self->interval_);
              self->retry_timer_.async_wait(
                [self](auto){ self->doConnect(); });
            } else if (self->secure_) {
              // handshake SSL
              self->socket_->async_handshake(
                ssl_socket_t::client,
                [self](auto ec3){
                  if (!ec3) {
                    // arrancar handlers de protocolo
                    self->addProtocolHandlers(self->socket_);
                  }
                  // en cualquier caso, when socket closes -> schedule reconnect
                  self->socket_->lowest_layer().async_wait(
                    boost::asio::socket_base::wait_read,
                    [self](auto, auto){
                      if (!self->stopped_) {
                        self->retry_timer_.expires_after(self->interval_);
                        self->retry_timer_.async_wait(
                          [self](auto){ self->doConnect(); });
                      }
                    });
                });
            } else {
              // sin SSL: arrancar directamente
              self->addProtocolHandlers(self->socket_);
              // schedule reconnect cuando cierre
              self->socket_->lowest_layer().async_wait(
                boost::asio::socket_base::wait_read,
                [self](auto, auto){
                  if (!self->stopped_) {
                    self->retry_timer_.expires_after(self->interval_);
                    self->retry_timer_.async_wait(
                      [self](auto){ self->doConnect(); });
                  }
                });
            }
          });
    });
}

} // namespace protocol
