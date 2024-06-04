#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common_src/clock.h"
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

    Queue<std::shared_ptr<Command>>& client_cmd_queue;
    BroadcasterSnapshots& broadcaster_snapshots;
    std::list<Player*>& players;

    bool* playing;
    bool still_waiting = false;
    bool game_ended = false;
    bool playing_done = false;

public:
    Gameloop(Queue<std::shared_ptr<Command>>& client_cmd_queue,
             BroadcasterSnapshots& broadcaster_snapshot, std::list<Player*>& players,
             bool* playing);

    std::shared_ptr<Snapshot> get_initial_snapshot(const Map& map);

    void run();

    void push_all_players(const Snapshot& snapshot);

    void stop();

    // ~Gameloop();
};

#endif
