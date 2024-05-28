#ifndef SERVERUSER_H
#define SERVERUSER_H

#include <list>
#include <memory>
#include <string>
#include <utility>

#include "../common_src/container_protocol.h"

#include "server_receiver.h"
#include "server_sender.h"

class Player {
private:
    std::shared_ptr<ContainerProtocol> container_protocol;
    int player_id;

    Queue<std::shared_ptr<Snapshot>> snapshots_queue;
    BroadcasterSnapshots& broadcaster_snapshots;
    ServerSender server_sender;

    Queue<std::shared_ptr<Command>> client_cmds_queue;
    ServerReceiver server_receiver;

    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;

public:
    Player(std::shared_ptr<ContainerProtocol> container_protocol, int player_id,
           BroadcasterSnapshots& broadcaster_snapshots,
           Queue<std::shared_ptr<Command>>& client_cmds_queue);
    void start();
    void join();
    Queue<std::shared_ptr<Snapshot>>& get_snapshots_queue();
    bool is_dead();
    void kill();
    ~Player();
};

#endif
