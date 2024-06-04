#ifndef MATCH_H
#define MATCH_H

#include <cstdint>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "../common_src/clock.h"
#include "../common_src/common_errors.h"
#include "../common_src/constants.h"
#include "../common_src/container_protocol.h"
#include "../common_src/queue.h"
#include "../common_src/snapshots/snapshot.h"
#include "../common_src/thread.h"
#include "../game_src/commands/command.h"
#include "../game_src/map.h"

#include "broadcaster_snapshots.h"
#include "config.h"
#include "constants_server.h"
#include "gameloop.h"
#include "player_info.h"
#include "server_player.h"


class Match: public Thread {

private:
    Map map;

    std::string match_name;
    std::shared_ptr<Queue<std::shared_ptr<PlayerInfo>>> matches_protocols_players_queue;

    int number_of_players;
    std::list<Player*> players;

    bool* playing;
    int* status;

    void send_players_ids();

    void send_game_initial(Gameloop game);

public:
    Match(std::shared_ptr<Queue<std::shared_ptr<PlayerInfo>>> matches_protocols_players_queue,
          Map map, const std::string& match_name, bool* playing, int* status);
    ~Match();

    bool has_started();

    void delete_players();

    uint8_t get_number_of_players();

    void run() override;

    std::string get_match_name();
};

#endif
