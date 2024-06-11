#include "server_player.h"

Player::Player(std::shared_ptr<ContainerProtocol> cont_protocol, int player_id,
               BroadcasterSnapshots& broadcaster_snapshots,
               Queue<std::shared_ptr<Command>>& client_cmds_queue):
        container_protocol(cont_protocol),
        player_id(player_id),
        snapshots_queue(QUEUE_MAX_SIZE),
        broadcaster_snapshots(broadcaster_snapshots),
        server_sender(container_protocol->protocol, broadcaster_snapshots, this->keep_talking, player_id),
        client_cmds_queue(client_cmds_queue),
        server_receiver(container_protocol->protocol, client_cmds_queue, this->keep_talking) {
    broadcaster_snapshots.add_player(player_id, &snapshots_queue);
}

void Player::start() {
    server_sender.start();
    server_receiver.start();
}

void Player::send_player_id() { container_protocol->protocol.send_response(player_id); }

int Player::get_id() { return player_id; }

bool Player::is_dead() {
    return !keep_talking;
}

void Player::join() {
    server_sender.join();
    std::cout<<"4"<<std::endl;
    server_receiver.join();
    std::cout<<"5"<<std::endl;
}

void Player::kill() {
    keep_talking = false;
    std::cout<<"1"<<std::endl;
    this->client_cmds_queue.close();
    std::cout<<"2"<<std::endl;
    this->container_protocol->protocol.kill();
    std::cout<<"3"<<std::endl;
}

Player::~Player() {}
