// include/TrackerClient.h
#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>
#include <vector>
#include <string>
#include <chrono>
#include "config/Config.h"

namespace protocol {

/// Cliente que se conecta periódicamente a un servidor TCP (opcionalmente SSL)
/// y reaplica los handlers de protocolo tras cada desconexión.
class TrackerClient : public std::enable_shared_from_this<TrackerClient> {
public:
    using steady_timer    = boost::asio::steady_timer;
    using tcp             = boost::asio::ip::tcp;
    using ssl_socket_t    = boost::asio::ssl::stream<tcp::socket>;

    /// @param io_context  el contexto de Asio
    /// @param config      tu objeto Config
    /// @param protocol    nombre del protocolo (prefijo en las claves)
    TrackerClient(boost::asio::io_context& io_context,
                  const config::Config& config,
                  const std::string& protocol);

    virtual ~TrackerClient();

    /// Inicia la conexión; tras un cierre, reintenta cada intervalo segundos.
    void start();

    /// Fuerza el cierre inmediato de la conexión y cancela futuros reintentos.
    void stop();

    bool isSecure() const noexcept { return secure_; }
    const std::vector<std::string>& devices() const noexcept { return devices_; }

protected:
    /// Igual que en Java: aquí tus subclases añaden los handlers de protocolo.
    virtual void addProtocolHandlers(std::shared_ptr<ssl_socket_t> socket) = 0;

private:
    void doConnect();
    void onConnect(const boost::system::error_code& ec);

    boost::asio::io_context&       io_context_;
    boost::asio::ssl::context      ssl_context_;
    std::unique_ptr<tcp::resolver> resolver_;
    std::shared_ptr<ssl_socket_t>  socket_;
    steady_timer                   retry_timer_;

    bool                           secure_;
    std::string                    host_;
    unsigned short                 port_;
    std::chrono::seconds           interval_;
    std::vector<std::string>       devices_;

    bool                           stopped_{false};
};

} // namespace protocol
