#include "client_manager.h"

ClientManager::ClientManager(const std::string& host, const std::string& service):
    protocol(std::move(host), std::move(service)), q_cmds(10), q_snapshots(),
    client_drawer(q_cmds, q_snapshots),
    client_sender(protocol, q_cmds), client_receiver(protocol, q_snapshots) {}

void ClientManager::run() {
    client_sender.start();
    client_receiver.start();
    client_drawer.run();
}

ClientManager::~ClientManager() {
    this->protocol.~Protocol();
    client_sender.kill();
    client_receiver.kill();
    client_receiver.join();
    client_sender.join();
}
