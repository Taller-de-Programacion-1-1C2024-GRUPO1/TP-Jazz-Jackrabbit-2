#include "map.h"

Map::Map(int width, int height, int amount_players, const std::string& map_name):
        map_name(map_name),
        width(width),
        height(height),
        amount_players(amount_players)
        {}

std::shared_ptr<Snapshot> Map::get_snapshot() const {
    Snapshot snapshot({}, {}, {});
    snapshot.set_dimensions(height, width, RABBIT_HEIGHT_DEFAULT, RABBIT_WIDTH_DEFAULT, amount_players);
    return std::make_shared<Snapshot>(snapshot);
}

std::string Map::get_name() const {
    return map_name;
}

Map::~Map() {}
