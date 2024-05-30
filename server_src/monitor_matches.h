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

#include "constants_server.h"
#include "map.h"
#include "match.h"
#include "match_info.h"

class MonitorMatches {
private:
    std::map<std::string, std::shared_ptr<MatchInfo>> matches;
    std::map<std::string, Map> maps;
    std::mutex mutex;

    void kill_dead_matches();

public:
    explicit MonitorMatches(const std::vector<std::string>& map_routes);

    // Agrega un nuevo match al monitor de matches
    int add_new_match(std::string match_name, std::shared_ptr<MatchInfo> match_info);

    // Muestra los matches disponibles
    std::map<std::string, std::string> show_matches_availables();

    // Un determinado usuario se une a un match
    int join_match(std::string match_name, std::shared_ptr<ContainerProtocol> container_protocolo);

    // Cierra los matches
    void close_matches();

    // Inicia un match
    void start_match(std::string match_name);

    Map get_map(std::string map_name);

    ~MonitorMatches();
};

#endif
