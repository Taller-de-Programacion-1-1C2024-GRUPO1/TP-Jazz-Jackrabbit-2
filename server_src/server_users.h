#ifndef SERVER_USER_H
#define SERVER_USER_H

#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "../common_src/common_socket.h"
#include "../common_src/protocol.h"
#include "../common_src/thread.h"
#include "../game_src/commands/command_match.h"
#include "../game_src/qt_response.h"

#include "constants_server.h"
#include "monitor_matches.h"
#include "player_info.h"
#include "server_player.h"


class User: public Thread {

private:
    int status;
    int id;
    std::shared_ptr<ContainerProtocol> container_protocol;
    MonitorMatches& monitor_matches;

    bool& server_running;

public:
    User(int current_id, std::shared_ptr<ContainerProtocol> container_protocol,
         MonitorMatches& monitor_matches, bool& server_running);
    void run() override;

    void create_new_match(int number_of_players, const std::string& match_name,
                          const std::string& map_name, ChampionType character_name,
                          std::string player_name);
    void join_match(const std::string& match_name, ChampionType character_name,
                    const std::string& player_name);
    void refresh();

    bool is_alive();

    void kill();
};

#endif
