#ifndef MATCH_H
#define MATCH_H

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cstdint>

#include <yaml-cpp/yaml.h>

#include "config.h"
#include "constants_server.h"

#include "../common_src/constants.h"
#include "../common_src/common_errors.h"
#include "../common_src/thread.h"
#include "../common_src/queue.h"
#include "../common_src/clock.h"
#include "../common_src/snapshots/snapshot.h"
#include "../common_src/container_protocol.h"

#include "../game_src/commands/command.h"
#include "../game_src/map.h"
#include "gameloop.h"

#include "server_player.h"
#include "broadcaster_snapshots.h"


class Match: public Thread {

private:
    Map map;

    std::string match_name;    
    std::shared_ptr<Queue<std::shared_ptr<ContainerProtocol>>> matches_protocols_queue ;
    
    int number_of_players;
    std::list<Player*> players;
    // game_map
    bool* keep_running;
    int* status;
    int id_counter;

    void send_game_initial(Game game);

public:
    // falta agregar el game_map
    Match(std::shared_ptr<Queue<std::shared_ptr<ContainerProtocol>>> matches_protocols_queue, std::string match_name, bool* keep_running, int* status);
    ~Match();

    bool has_started();

    void delete_players();

    uint8_t get_number_of_players();

    void run() override;

    std::string get_match_name();
};

#endif
