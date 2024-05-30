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
                create_new_match(new_match->get_match_name(), new_match->get_map_name());
            } else if (new_match->getType() == JOIN) {
                join_match(new_match->get_match_name());
            } else if (new_match->getType() == REFRESH) {
                refresh();
            } else if (new_match->getType() == START_MATCH) {
                start_match(new_match->get_match_name());
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

void User::create_new_match(const std::string& match_name, const std::string& map_name) {

    std::shared_ptr<Queue<std::shared_ptr<ContainerProtocol>>> protocols_queue =
            std::make_shared<Queue<std::shared_ptr<ContainerProtocol>>>();
    protocols_queue->push(this->container_protocol);

    std::shared_ptr<MatchInfo> new_match =
            std::make_shared<MatchInfo>(match_name, map_name, protocols_queue, playing);

    int ACK = monitor_matches.add_new_match(match_name, new_match);

    container_protocol->protocol.send_user_joined_match(ACK);
    if (ACK == ERROR) {
        return;
    }
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
std::vector<Rabbit> User::create_rabbits(std::vector<SpawnPoints> rabbit_spawns){
    std::vector<Rabbit> rabbits;
    for (long unsigned int i = 0; i < rabbit_spawns.size(); i++) {
        rabbits.push_back(Rabbit(rabbit_spawns[i].x, rabbit_spawns[i].y, rabbit_spawns[i].id));
    }
    return rabbits;
}
*/

// cambiar "Player" a rabbit
std::unordered_map<int, Player> User::make_players_map(const std::vector<Player>& player) {
    std::unordered_map<int, Player> players_map;
    for (long unsigned int i = 0; i < player.size(); i++) {
        // players_map.emplace(player[i].get_id(), player[i]);
    }
    return players_map;
}

bool User::is_alive() { return status == ACTIVE; }

void User::kill() {
    try {
        this->container_protocol->protocol.~Protocol();
    } catch (const std::exception& e) {}
    this->status = INACTIVE;
}

User::~User() {}
