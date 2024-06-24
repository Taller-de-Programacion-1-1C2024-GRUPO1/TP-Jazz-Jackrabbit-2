#ifndef MONITOR_MATCHES_H
#define MONITOR_MATCHES_H

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../common_src/constants.h"
#include "../common_src/queue.h"
#include "../common_src/snapshots/snapshot.h"
#include "../game_src/map_reader.h"

#include "constants_server.h"
#include "map.h"
#include "match.h"
#include "match_info.h"

class MonitorMatches {
private:
    MapReader map_reader;
    std::map<std::string, std::shared_ptr<MatchInfo>> matches;
    std::map<std::string, std::shared_ptr<Map>> maps;
    std::mutex mutex;

    void kill_dead_matches();

public:
    explicit MonitorMatches(const std::string& map_routes);

    // Agrega un nuevo match al monitor de matches
    int add_new_match(std::string match_name, std::shared_ptr<MatchInfo> match_info);

    // Muestra los matches disponibles
    std::vector<std::string> show_matches_availables();

    std::vector<std::string> show_maps_availables();

    // Un determinado usuario se une a un match
    int join_match(std::string match_name, std::shared_ptr<ContainerProtocol> container_protocolo,
                   int id, ChampionType character_name, std::string player_name);

    // Cierra los matches
    void close_matches();

    // Inicia un match
    void start_match(std::string match_name);

    std::shared_ptr<Map> get_map(std::string map_name);

    ~MonitorMatches();
};

#endif
