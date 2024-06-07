#include "server_receiver.h"

#include "../game_src/commands/command.h"
ServerReceiver::ServerReceiver(Protocol& protocol,
                               Queue<std::shared_ptr<Command>>& client_cmds_queue):
        protocol(protocol),
        client_cmds_queue(client_cmds_queue),
        keep_talking(true),
        is_alive(true) {}


void ServerReceiver::run() {
    while (keep_talking) {
        try {
            std::shared_ptr<Command> cmd = this->protocol.receive_Command();
            this->client_cmds_queue.push(cmd);
        } catch (const ClosedQueue& e) {
            std::cerr << "The queue client_cmds_q is closed" << std::endl;
            kill();
            break;
        } catch (const std::exception& e) {
            std::cerr << "Error not expected: " << e.what() << std::endl;
            kill();
            break;
        }
    }
    this->is_alive = false;
}


bool ServerReceiver::is_dead() { return !this->is_alive; }


void ServerReceiver::kill() { this->keep_talking = false; }


ServerReceiver::~ServerReceiver() {}
