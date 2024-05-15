#include "server_player.h"

ServerPlayer::ServerPlayer(Socket&& peer, Queue<uint8_t>& client_cmds_q,
                       ProtectedListOfQueues& list_of_q_msgs):
        protocol(std::move(peer)),
        list_of_q_msgs(list_of_q_msgs),
        server_sender(protocol, list_of_q_msgs),
        client_cmds_q(client_cmds_q),
        server_receiver(protocol, client_cmds_q) {}

void ServerPlayer::run() {
    server_sender.start();
    server_receiver.start();
}

bool ServerPlayer::is_dead() {
    if (server_sender.is_dead() && server_receiver.is_dead()) {
        return true;
    }
    return false;
}

void ServerPlayer::kill() {
    this->protocol.~ServerProtocol();
    server_sender.kill();
    server_receiver.kill();
    server_receiver.join();
    server_sender.join();
}


ServerPlayer::~ServerPlayer() {}
