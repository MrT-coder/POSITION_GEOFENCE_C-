#include <cstdlib>
#include <filesystem>
#include <thread>
#include <vector>
#include <utility>

#include <boost/asio.hpp>
#include <crow.h>

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "decoder.h"

using boost::asio::ip::udp;
using boost::asio::ip::tcp;
using bsoncxx::builder::stream::document;

int main() {
    // 0. Configuración de logging
    auto logger = spdlog::basic_logger_mt("posgeo_server", "logs/posgeo_server.txt");
    spdlog::set_default_logger(logger);
    spdlog::set_level(spdlog::level::debug);
    spdlog::flush_on(spdlog::level::info);
    spdlog::info("=== posgeo_server arrancando ===");

    // 1. Configurar y probar conexión a MongoDB
    const char* uri_env = std::getenv("MONGO_URI");
    std::string uri = uri_env ? uri_env : "mongodb://localhost:28018";
    spdlog::debug("Conectando a MongoDB en {}", uri);

    mongocxx::instance inst{};
    mongocxx::client client{mongocxx::uri{uri}};
    try {
        auto ping = client["admin"].run_command(
            bsoncxx::builder::basic::make_document(
                bsoncxx::builder::basic::kvp("ping", 1)
            )
        );
        spdlog::info("Mongo ping response: {}", bsoncxx::to_json(ping.view()));
    } catch (const std::exception& e) {
        spdlog::critical("No se pudo hacer ping a MongoDB: {}", e.what());
        return EXIT_FAILURE;
    }
    auto db = client["iot"];
    auto devices_col = db["devices"];

    // 2. Contexto de Boost.Asio
    boost::asio::io_context io_context;

    // 3. Inicializar servidor HTTP de Crow
    crow::App<> app;
    spdlog::info("HTTP servidor configurado en puerto 8080");

    // 4. Señales para shutdown limpio
    boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
    signals.async_wait([&](const boost::system::error_code& ec, int signo) {
        if (!ec) {
            spdlog::info("Señal {} recibida: deteniendo servicio...", signo);
            app.stop();
            io_context.stop();
        }
    });

    // 5. Servidor UDP
    udp::socket udp_sock(io_context, udp::endpoint(udp::v4(), 4000));
    spdlog::info("Servidor UDP escuchando en puerto 4000");
    udp::endpoint udp_endpoint;
    std::vector<uint8_t> udp_buffer(1024);

    std::function<void(const boost::system::error_code&, std::size_t)> handle_udp;
    handle_udp = [&](auto ec, std::size_t bytes) {
        if (!ec && bytes > sizeof(uint32_t)) {
            std::vector<uint8_t> data(udp_buffer.begin(), udp_buffer.begin() + bytes);
            auto msg = decode_message(data);
            spdlog::debug("UDP recibido ({} bytes): {}", bytes, msg);

            document doc{};
            doc << "data" << msg;
            devices_col.insert_one(doc.view());
            spdlog::info("UDP → insert_one OK");
        } else if (ec) {
            spdlog::error("Error en UDP receive: {}", ec.message());
        }
        udp_sock.async_receive_from(
            boost::asio::buffer(udp_buffer),
            udp_endpoint,
            handle_udp
        );
    };
    udp_sock.async_receive_from(
        boost::asio::buffer(udp_buffer),
        udp_endpoint,
        handle_udp
    );

    // 6. Servidor TCP
    tcp::acceptor acceptor(io_context, {tcp::v4(), 5000});
    spdlog::info("Servidor TCP escuchando en puerto 5000");
    std::function<void()> do_accept;
    do_accept = [&]() {
        auto sock = std::make_shared<tcp::socket>(io_context);
        acceptor.async_accept(*sock, [&, sock](auto ec) {
            if (!ec) {
                spdlog::debug("TCP conexión aceptada");
                auto buf = std::make_shared<std::vector<uint8_t>>(1024);
                sock->async_read_some(
                    boost::asio::buffer(*buf),
                    [&, buf](auto ec2, std::size_t len) {
                        if (!ec2 && len > sizeof(uint32_t)) {
                            std::vector<uint8_t> data(buf->begin(), buf->begin() + len);
                            auto msg = decode_message(data);
                            spdlog::debug("TCP recibido ({} bytes): {}", len, msg);

                            document doc{};
                            doc << "data" << msg;
                            devices_col.insert_one(doc.view());
                            spdlog::info("TCP → insert_one OK");
                        } else if (ec2) {
                            spdlog::error("Error en TCP read: {}", ec2.message());
                        }
                    }
                );
            } else {
                spdlog::error("Error en TCP accept: {}", ec.message());
            }
            do_accept();
        });
    };
    do_accept();

    // 7. Ejecutar io_context en hilo aparte
    std::thread asio_thread([&]() {
        spdlog::info("io_context.run() iniciado");
        io_context.run();
    });

    // 8. HTTP endpoint /device
    CROW_ROUTE(app, "/device")([&]() {
        try {
            crow::json::wvalue res;
            int i = 0;
            for (auto&& d : devices_col.find({})) {
                res["devices"][i++] = bsoncxx::to_json(d);
            }
            spdlog::info("Endpoint /device → {} dispositivos", i);
            return crow::response{res};
        } catch (const std::exception& e) {
            spdlog::error("Error en /device: {}", e.what());
            return crow::response{500, std::string("DB error: ") + e.what()};
        }
    });

    // 9. Arrancar HTTP (bloqueante)
    app.port(8080)
       .concurrency(std::thread::hardware_concurrency())
       .run();

    // 10. Esperar al hilo de Asio y cerrar
    asio_thread.join();
    spdlog::info("device_server finalizado correctamente");
    return 0;
}
