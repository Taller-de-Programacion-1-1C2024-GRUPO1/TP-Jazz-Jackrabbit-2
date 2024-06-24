#include "server_users.h"

User::User(int current_id, std::shared_ptr<ContainerProtocol> container_protocol,
           MonitorMatches& monitor_matches, bool& server_running):
        status(ACTIVE),
        id(current_id),
        container_protocol(container_protocol),
        monitor_matches(monitor_matches),
        server_running(server_running) {}

void User::run() {
    try {
        while (status == ACTIVE) {
            std::shared_ptr<Command> command = container_protocol->protocol.receive_Command();
            std::shared_ptr<MatchCommand> new_match =
                    std::dynamic_pointer_cast<MatchCommand>(command);
            if (new_match->getType() == NEW_MATCH) {
                create_new_match(new_match->get_number_players(), new_match->get_match_name(),
                                 new_match->get_map_name(), new_match->get_character_name(),
                                 new_match->get_player_name());
            } else if (new_match->getType() == JOIN) {
                join_match(new_match->get_match_name(), new_match->get_character_name(),
                           new_match->get_player_name());
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
                            const std::string& map_name, ChampionType character_name,
                            std::string player_name) {

    std::shared_ptr<Queue<std::shared_ptr<PlayerInfo>>> protocols_queue =
            std::make_shared<Queue<std::shared_ptr<PlayerInfo>>>();

    std::shared_ptr<PlayerInfo> player_info =
            std::make_shared<PlayerInfo>(this->id, character_name, container_protocol, player_name);

    protocols_queue->push(player_info);

    std::shared_ptr<MatchInfo> new_match =
            std::make_shared<MatchInfo>(match_name, monitor_matches.get_map(map_name),
                                        protocols_queue, server_running, number_of_players);

    int ACK = monitor_matches.add_new_match(match_name, new_match);

    QtResponse response = QtResponse(ACK, NEW_MATCH);
    response.send(container_protocol->protocol);

    if (ACK == ERROR) {
        return;
    }
    monitor_matches.start_match(match_name);
    this->status = INACTIVE;
}

void User::join_match(const std::string& match_name, ChampionType character_name,
                      const std::string& player_name) {
    // se fija si el match esta vivo
    int ACK = monitor_matches.join_match(match_name, container_protocol, this->id, character_name,
                                         player_name);

    QtResponse response = QtResponse(ACK, JOIN);
    response.send(container_protocol->protocol);

    if (ACK == ERROR) {
        return;
    }
    this->status = INACTIVE;
}

void User::refresh() {
    std::vector<std::string> matches_availables = monitor_matches.show_matches_availables();
    std::vector<std::string> maps_availables = monitor_matches.show_maps_availables();
    std::tuple<std::vector<std::string>, std::vector<std::string>> response_tuple =
            std::make_tuple(matches_availables, maps_availables);
    QtResponse response = QtResponse(response_tuple, REFRESH);
    response.send(container_protocol->protocol);
}

bool User::is_alive() { return status == ACTIVE; }

void User::kill() {
    try {
        this->container_protocol->protocol.kill();
    } catch (const std::exception& e) {
        return;
    }
    this->status = INACTIVE;
}
