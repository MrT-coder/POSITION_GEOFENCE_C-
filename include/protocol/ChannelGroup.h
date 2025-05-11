// include/protocol/ChannelGroup.h
#pragma once

#include <vector>
#include <memory>
#include <asio/ip/tcp.hpp>
#include <asio/ip/udp.hpp>

namespace protocol {

/// Agrupa sockets TCP y UDP para cerrarlos en bloque
class ChannelGroup {
public:
    using TcpSocketPtr = std::shared_ptr<asio::ip::tcp::socket>;
    using UdpSocketPtr = std::shared_ptr<asio::ip::udp::socket>;

    /// Añade un socket TCP al grupo
    void add(const TcpSocketPtr& sock) {
        tcpSockets_.push_back(sock);
    }

    /// Añade un socket UDP al grupo
    void add(const UdpSocketPtr& sock) {
        udpSockets_.push_back(sock);
    }

    /// Cierra todos los sockets agrupados
    void close() {
        for (auto& s : tcpSockets_) { if (s && s->is_open()) s->close(); }
        for (auto& s : udpSockets_) { if (s && s->is_open()) s->close(); }
    }

private:
    std::vector<TcpSocketPtr> tcpSockets_;
    std::vector<UdpSocketPtr> udpSockets_;
};

} // namespace protocol
