#include "monitor_matches.h"

MonitorMatches::MonitorMatches(const std::string& map_routes): map_reader(map_routes) {
    std::map<std::string, Map> maps = map_reader.get_maps();
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
    matches[match_name]->match_starter->start();
}

std::map<std::string, std::string> MonitorMatches::show_matches_availables() {
    std::map<std::string, std::string> availableMatches;
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& match: matches) {
        if (match.second->status == MATCH_WAITING) {
            availableMatches[match.first] = match.second->map_name;
        }
    }
    return availableMatches;
}

int MonitorMatches::join_match(std::string match_name,
                               std::shared_ptr<ContainerProtocol> cont_protocol) {
    std::lock_guard<std::mutex> lock(mutex);
    if (matches[match_name]->status == MATCH_ALIVE || matches[match_name]->status == MATCH_OVER) {
        return ERROR;
    }
    // agrego jugador al match
    std::shared_ptr<Queue<std::shared_ptr<ContainerProtocol>>> matches_protocols_queue =
            matches[match_name]->matches_protocols_queue;
    matches_protocols_queue->push(cont_protocol);
    return OK;
}

Map MonitorMatches::get_map(std::string map_name) {
    std::lock_guard<std::mutex> lock(mutex);
    return maps[map_name];
}

void MonitorMatches::close_matches() {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& match: matches) {
        match.second->matches_protocols_queue->close();
        match.second->match_starter->join();
    }
    matches.clear();
}

void MonitorMatches::kill_dead_matches() {
    std::vector<std::string> delete_matches;
    for (auto& match: matches) {
        if (match.second->status == MATCH_OVER) {
            match.second->matches_protocols_queue->close();
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
