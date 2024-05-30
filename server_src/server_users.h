#ifndef SERVER_USER_H
#define SERVER_USER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common_src/common_socket.h"
#include "../common_src/protocol.h"
#include "../common_src/thread.h"
#include "../game_src/commands/command_match.h"

#include "constants_server.h"

// #include "match.h"
// #include "match_struct.h"
#include "monitor_matches.h"
#include "server_player.h"

class User: public Thread {

private:
    int status;

    std::shared_ptr<ContainerProtocol> container_protocol;
    MonitorMatches& monitor_matches;

    bool* playing;

    std::unordered_map<int, Player> make_players_map(const std::vector<Player>& server_player);

public:
    User(std::shared_ptr<ContainerProtocol> container_protocol, MonitorMatches& monitor_matches,
         bool* playing);
    void run() override;

    void create_new_match(const std::string& match_name, const std::string& map_name);
    void start_match(const std::string& match_name);
    void join_match(const std::string& match_name);
    void refresh();

    bool is_alive();

    void kill();
    ~User();
};

#endif
