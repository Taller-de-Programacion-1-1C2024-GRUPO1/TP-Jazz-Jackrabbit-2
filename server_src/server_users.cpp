#include "server_users.h"

User::User(std::shared_ptr<ContainerProtocol> container_protocol, MonitorMatches& monitor_matches,
           bool* playing):
        status(ACTIVE),
        container_protocol(container_protocol),
        monitor_matches(monitor_matches),
        playing(playing) {}

void User::run() {
    try {
        while (status == ACTIVE) {
            std::shared_ptr<Command> command = container_protocol->protocol.receive_Command();
            std::shared_ptr<MatchCommand> new_match =
                    std::dynamic_pointer_cast<MatchCommand>(command);
            if (new_match->get_commandType() == NEW_MATCH) {
                create_new_match(new_match->get_number_of_players(), new_match->get_match_name(),
                                 new_match->get_map_name());
            } else if (new_match->getType() == JOIN) {
                join_match(new_match->get_match_name());
            } else if (new_match->getType() == REFRESH) {
                refresh();
            }
        }
    } catch (const LostConnection& e) {
        kill();
        return;
    } catch (const std::exception& e) {
        kill();
        return;
    }
}

void User::create_new_match(int number_of_players, const std::string& match_name,
                            const std::string& map_name) {

    Map map = monitor_matches.get_map(map_name);
    // std::vector<Rabbit> rabbits = create_rabbits(map.rabbits);

    std::shared_ptr<Queue<std::shared_ptr<ContainerProtocol>>> protocols_queue =
            std::make_shared<Queue<std::shared_ptr<ContainerProtocol>>>();
    protocols_queue->push(this->container_protocol);
    // std::unordered_map<int, Rabbit> rabbitsMap = make_players_map(rabbits);
    // std::shared_ptr<GameMap> game_map = std::make_shared<GameMap>(GameMap(numberPlayers,
    // map_name, map));

    // agregar el game_map
    std::shared_ptr<MatchInfo> new_match =
            std::make_shared<MatchInfo>(match_name, map_name, protocols_queue, playing);

    int ACK = monitor_matches.add_new_match(match_name, new_match);
    container_protocol->protocol.send_user_created_match(ACK);
    if (ACK == ERROR) {
        return;
    }
    monitor_matches.start_match(match_name);
    this->status = INACTIVE;
}

void User::start_match(const std::string& match_name) { monitor_matches.start_match(match_name); }

void User::join_match(const std::string& match_name) {
    // se fija si el match esta vivo
    int ACK = monitor_matches.join_match(match_name, container_protocol);
    if (ACK == ERROR) {
        return;
    }
    // enviar mensaje de que se unio correctamente
    container_protocol->protocol.send_user_joined_match(ACK);
    this->status = INACTIVE;
}

void User::refresh() {
    /*
    GameInfo information(matches_monitor.show_matches_available());
    container_protocol->protocol.send_info_matches(&info);
    */
}

/*
std::unordered_map<int, Player> User::make_players_map(const std::vector<Player>& player) {
    std::unordered_map<int, Player> players_map;
    for (long unsigned int i = 0; i < player.size(); i++) {
        // players_map.emplace(player[i].get_id(), player[i]);
    }
    return players_map;
}
*/

bool User::is_alive() { return status == ACTIVE; }

void User::kill() {
    try {
        this->container_protocol->protocol.~Protocol();
    } catch (const std::exception& e) {}
    this->status = INACTIVE;
}

User::~User() {}
