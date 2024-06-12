#ifndef SERVERUSER_H
#define SERVERUSER_H

#include <list>
#include <memory>
#include <string>
#include <utility>

#include "../common_src/container_protocol.h"
#include "../game_src/qt_response.h"

#include "server_receiver.h"
#include "server_sender.h"

class Player {
private:
    std::shared_ptr<ContainerProtocol> container_protocol;
    int player_id;

    Queue<std::shared_ptr<Snapshot>> snapshots_queue;
    BroadcasterSnapshots& broadcaster_snapshots;
    ServerSender server_sender;

    Queue<std::shared_ptr<Command>>& client_cmds_queue;
    ServerReceiver server_receiver;

    bool keep_talking = true;

public:
    Player(std::shared_ptr<ContainerProtocol> container_protocol, int player_id,
           BroadcasterSnapshots& broadcaster_snapshots,
           Queue<std::shared_ptr<Command>>& client_cmds_queue);
    void start();
    void send_player_id();
    int get_id();
    bool is_dead();
    void join();
    void kill();
};

#endif
