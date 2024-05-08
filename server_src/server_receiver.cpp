#include "server_receiver.h"


ServerReceiver::ServerReceiver(ServerProtocol& protocol, Queue<uint8_t>& client_cmds_q):
        protocol(protocol), client_cmds_q(client_cmds_q), keep_talking(true), is_alive(true) {}


void ServerReceiver::run() {
    while (keep_talking) {
        try {
            uint8_t msg = this->protocol.get_byte();
            this->client_cmds_q.push(msg);
        } catch (const ClosedQueue& e) {
            std::cerr << "The queue client_cmds_q is closed" << std::endl;

        } catch (const std::exception& e) {
            // std::cerr << "No pude recibir comando o se cerro el cliente forzadamente" <<
            // std::endl;
            break;
        }
    }
    this->is_alive = false;
}


bool ServerReceiver::is_dead() { return !this->is_alive; }


void ServerReceiver::kill() { this->keep_talking = false; }


ServerReceiver::~ServerReceiver() {}
