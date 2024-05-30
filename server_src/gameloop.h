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


class Game {
private:
    int height;
    int width;

    Queue<std::shared_ptr<Command>>& client_cmd_queue;
    BroadcasterSnapshots& broadcaster_snapshots;
    std::list<Player*>& players;

    bool* playing;

    // GameWorld game_world; -> contiene el game_map

    // int rabbit_playing_id;
    // int rabbit_playing_health;
    // int rabbit_playing_score;

    bool still_waiting = false;

    bool game_ended = false;
    bool playing_done = false;

    // GameManager game_manager;

    // EN GAME MANAGER SE INCLUIRAN LOS SIGUIENTES MANAGERS
    // PlayerManager player_manager;
    // SupplyManager box_manager;
    // ProjectileManager projectile_manager;

    // GameBuilder builder;

public:
    Game(Queue<std::shared_ptr<Command>>& client_cmd_queue,
         BroadcasterSnapshots& broadcaster_snapshot, std::list<Player*>& players, bool* playing);

    std::shared_ptr<Snapshot> get_initial_snapshot(const Map& map);

    void run();

    void execute_and_step(int iter);

    void push_all_players(const Snapshot& snapshot);

    void stop();

    // ~Game();
};

#endif
