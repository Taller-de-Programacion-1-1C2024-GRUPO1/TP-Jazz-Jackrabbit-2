#include "client_protocol.h"

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
