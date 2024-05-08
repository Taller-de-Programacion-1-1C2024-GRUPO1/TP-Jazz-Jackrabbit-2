
#include "protocol.h"


// Protocol
Protocol::Protocol(const std::string& host, const std::string& service):
        hostname(host), servname(service), socket(host.c_str(), service.c_str()) {}


Protocol::Protocol(Socket peer): socket(std::move(peer)), was_closed(false) {}


bool Protocol::is_close() { return this->was_closed; }


Protocol::~Protocol() {
    this->was_closed = true;
    this->socket.~Socket();
}


// ClientProtocol
ClientProtocol::ClientProtocol(const std::string& host, const std::string& service):
        Protocol(host, service) {}

bool ClientProtocol::send_byte(uint8_t& msg) {
    int sz = this->socket.sendall(&msg, 1, &this->was_closed);  // envio 1 byte
    if (sz <= 0) {
        return false;  // Si no se recibieron bytes o ocurrió un error, retornamos false
    }
    return true;
}


void ClientProtocol::get_msg(Message& msg) {
    try {
        int sz_1 = this->socket.recvall(&msg.msg_indicator, 1, &was_closed);
        uint16_t new_num_alive_enemies;
        int sz_2 = this->socket.recvall(&new_num_alive_enemies, 2, &was_closed);
        msg.num_alive_enemies = ntohs(new_num_alive_enemies);
        uint16_t new_num_dead_enemies;
        int sz_3 = this->socket.recvall(&new_num_dead_enemies, 2, &was_closed);
        msg.num_dead_enemies = ntohs(new_num_dead_enemies);
        int sz_4 = this->socket.recvall(&msg.event_type, 1, &was_closed);
        if (sz_1 <= 0 or sz_2 <= 0 or sz_3 <= 0 or sz_4 <= 0 or this->was_closed) {
            throw std::runtime_error("No se recibio el el mensaje o el socket estaba cerrado");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error en la recepción de mensajes del client protocol" << std::endl;
    }
}


// ServerProtocol
ServerProtocol::ServerProtocol(Socket peer): Protocol(std::move(peer)) {}


void ServerProtocol::send_server_enemy_status_count(const Message& msg) {
    this->socket.sendall(&msg.msg_indicator, 1, &this->was_closed);
    uint16_t new_num_alive_enemies = htons(msg.num_alive_enemies);
    this->socket.sendall(&new_num_alive_enemies, 2, &this->was_closed);
    uint16_t new_num_dead_enemies = htons(msg.num_dead_enemies);
    this->socket.sendall(&new_num_dead_enemies, 2, &this->was_closed);
    this->socket.sendall(&msg.event_type, 1, &this->was_closed);
}


uint8_t ServerProtocol::get_byte() {
    uint8_t buf;
    try {
        int sz = this->socket.recvall(&buf, sizeof(buf), &was_closed);
        if (sz <= 0) {
            throw std::runtime_error("ServerProtocol::get_byte() could not receive.");
        }
        return buf;
    } catch (const std::exception& e) {
        throw;
    }
}
