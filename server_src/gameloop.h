#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common_src/constants.h"
#include "../common_src/queue.h"
#include "../common_src/snapshots/snapshot.h"
#include "../game_src/commands/command.h"
#include "../game_src/map.h"

#include "broadcaster_snapshots.h"
#include "constants_server.h"
#include "server_player.h"


class Gameloop {
private:
    Queue<std::shared_ptr<Command>>& client_cmds_queue;
    BroadcasterSnapshots& broadcaster_snapshots;
    std::list<Player*>& players;
    std::shared_ptr<Map> map;

    bool& server_running;
    bool& playing;
    bool game_ended = false;

public:
    Gameloop(Queue<std::shared_ptr<Command>>& client_cmds_queue,
             BroadcasterSnapshots& broadcaster_snapshot, std::list<Player*>& players,
             std::shared_ptr<Map> map, bool& server_running, bool& playing);

    void send_initial_snapshots();

    void run();

    void push_all_players(const Snapshot& snapshot);

    void stop();

    void check_players();
};

#endif
