
#include "client_sender.h"

#include <chrono>

ClientSender::ClientSender(ClientProtocol& protocol, Queue<Command>& q_cmds):
        protocol(protocol), q_cmds(q_cmds), keep_talking(true), is_alive(true) {}


void ClientSender::run() {
    while (keep_talking) {
        try {
            // Command cmd = q_cmds.pop();
            // this->protocol.send(cmd);
            std::cout << "Client SENDER: Enviando comando" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        } catch (const ClosedQueue& e) {
            std::cerr << "Se cerró la Command queue" << std::endl;
            break;
        } catch (const std::exception& e) {
            std::cerr
                    << "Client SENDER: error al enviar comando o se cerro el servidor forzadamente"
                    << std::endl;
            break;
        }
    }
    this->is_alive = false;
}


bool ClientSender::is_dead() { return !this->is_alive; }


void ClientSender::kill() {
    this->keep_talking = false;
    q_cmds.close();
}
