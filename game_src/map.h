#ifndef MAP_H
#define MAP_H

#include <memory>
#include <string>
#include <vector>

#include "../common_src/snapshots/snapshot.h"

class Map {
public:
    std::string map_name;
    int width;
    int height;
    int amount_players;

    Map(int width, int height, int amount_players, const std::string& map_name);

    Map() {}

    std::shared_ptr<Snapshot> get_snapshot() const;

    std::string get_name() const;

    ~Map();
};

#endif
