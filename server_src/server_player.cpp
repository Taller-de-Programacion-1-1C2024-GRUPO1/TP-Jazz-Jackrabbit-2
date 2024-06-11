#include "server_player.h"

Player::Player(std::shared_ptr<ContainerProtocol> cont_protocol, int player_id,
               BroadcasterSnapshots& broadcaster_snapshots,
               Queue<std::shared_ptr<Command>>& client_cmds_queue):
        container_protocol(cont_protocol),
        player_id(player_id),
        snapshots_queue(QUEUE_MAX_SIZE),
        broadcaster_snapshots(broadcaster_snapshots),
        server_sender(container_protocol->protocol, broadcaster_snapshots, player_id),
        client_cmds_queue(client_cmds_queue),
        server_receiver(container_protocol->protocol, client_cmds_queue) {
    broadcaster_snapshots.add_player(player_id, &snapshots_queue);
}

void Player::start() {
    server_sender.start();
    server_receiver.start();
}

void Player::send_player_id() {
    QtResponse response = QtResponse(player_id, PLAYER_CONNECTING);
    response.send(container_protocol->protocol);
}

int Player::get_id() { return player_id; }

bool Player::is_dead() {
    if (server_sender.is_dead() && server_receiver.is_dead()) {
        return true;
    }
    return false;
}

void Player::kill() {
    this->container_protocol->protocol.~Protocol();
    this->client_cmds_queue.close();
    server_sender.kill();
    server_receiver.kill();
    server_sender.join();
    server_receiver.join();
}

Player::~Player() {}
