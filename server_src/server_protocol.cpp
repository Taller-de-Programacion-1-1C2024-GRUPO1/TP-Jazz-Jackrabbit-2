#include "server_protocol.h"

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
