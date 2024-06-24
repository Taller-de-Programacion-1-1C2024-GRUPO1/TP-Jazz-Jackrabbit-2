#include "monitor_matches.h"

MonitorMatches::MonitorMatches(const std::string& map_routes): map_reader(map_routes) {
    map_reader.get_maps(maps);
}

int MonitorMatches::add_new_match(std::string match_name, std::shared_ptr<MatchInfo> match_struct) {
    std::lock_guard<std::mutex> lock(mutex);
    kill_dead_matches();
    auto name = matches.find(match_name);
    if (name != matches.end()) {
        return ERROR;
    }
    matches[match_name] = match_struct;
    return OK;
}

void MonitorMatches::start_match(std::string match_name) {
    std::cout << "Starting match..." << std::endl;
    matches[match_name]->match_starter->start();
}

std::vector<std::string> MonitorMatches::show_matches_availables() {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<std::string> availableMatches;
    for (auto& match: matches) {
        if (match.second->status == MATCH_WAITING) {
            availableMatches.push_back(match.first);
        }
    }
    return availableMatches;
}

std::vector<std::string> MonitorMatches::show_maps_availables() {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<std::string> availableMaps;
    for (auto& map: maps) {
        // Linea para no tomar los que comienzen con el prefijo: "DEFAULT"
        /*
        if (map.first.find("default") != std::string::npos) {
            continue;
        }
        */
        availableMaps.push_back(map.first);
    }
    return availableMaps;
}

int MonitorMatches::join_match(std::string match_name,
                               std::shared_ptr<ContainerProtocol> cont_protocol, int id,
                               ChampionType character_name, std::string player_name) {
    std::lock_guard<std::mutex> lock(mutex);
    // chequeo si la partida existe
    auto name = matches.find(match_name);
    if (name == matches.end()) {
        return ERROR;
    }
    // chequeo si la partida esta viva o terminada
    if (matches[match_name]->status == MATCH_ALIVE || matches[match_name]->status == MATCH_OVER) {
        return ERROR;
    }
    // agrego jugador al match
    std::shared_ptr<Queue<std::shared_ptr<PlayerInfo>>> matches_protocols_queue =
            matches[match_name]->matches_protocols_players_queue;
    std::shared_ptr<PlayerInfo> player_info =
            std::make_shared<PlayerInfo>(id, character_name, cont_protocol, player_name);
    matches_protocols_queue->push(player_info);
    return OK;
}

std::shared_ptr<Map> MonitorMatches::get_map(std::string map_name) {
    std::lock_guard<std::mutex> lock(mutex);
    map_reader.refresh_load_maps(maps);
    return maps[map_name];
}

void MonitorMatches::close_matches() {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& match: matches) {
        match.second->matches_protocols_players_queue->close();
        match.second->match_starter->join();
    }
    matches.clear();
}

void MonitorMatches::kill_dead_matches() {
    std::vector<std::string> delete_matches;
    for (auto& match: matches) {
        if (match.second->status == MATCH_OVER) {
            match.second->matches_protocols_players_queue->close();
            match.second->match_starter->join();
            delete_matches.push_back(match.first);
        }
    }
    for (long unsigned int i = 0; i < delete_matches.size(); i++) {
        matches.erase(delete_matches[i]);
    }
}

MonitorMatches::~MonitorMatches() {
    for (auto& match: matches) {
        match.second->match_starter->join();
    }
}
