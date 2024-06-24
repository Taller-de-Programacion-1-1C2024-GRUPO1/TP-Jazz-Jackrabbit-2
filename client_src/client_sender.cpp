#include "client_sender.h"


ClientSender::ClientSender(Protocol& protocol, Queue<std::unique_ptr<Command>>& q_cmds):
        protocol(protocol), q_cmds(q_cmds), keep_talking(true), is_alive(true) {}


void ClientSender::run() {
    while (keep_talking) {
        try {
            std::unique_ptr<Command> cmd = q_cmds.pop();
            cmd->send(this->protocol);

        } catch (const ClosedQueue& e) {
            // std::cerr << "Command queue was closed" << std::endl;
            break;
        } catch (const std::exception& e) {
            // std::cerr << "Client SENDER: error sending command or the server was forcibly closed"
            // << std::endl;
            break;
        }
    }
    q_cmds.close();
    this->is_alive = false;
}


bool ClientSender::is_dead() { return !this->is_alive; }


void ClientSender::kill() { this->keep_talking = false; }
