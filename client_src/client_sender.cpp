
#include "client_sender.h"

#include <chrono>

ClientSender::ClientSender(Protocol& protocol, Queue<std::unique_ptr<Command>>& q_cmds):
        protocol(protocol), q_cmds(q_cmds), keep_talking(true), is_alive(true) {}


void ClientSender::run() {
    while (keep_talking) {
        try {
            bool could_pop = false;
            std::unique_ptr<Command> cmd;
            while (!could_pop && keep_talking) {
                could_pop =  q_cmds.try_pop(cmd);
            }
            if (could_pop) {
                cmd->send(this->protocol);
                std::cout << "Client SENDER: Enviando comando" << std::endl;
            }
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
    q_cmds.close();
    this->is_alive = false;
}


bool ClientSender::is_dead() { return !this->is_alive; }


void ClientSender::kill() {
    this->keep_talking = false;
}
