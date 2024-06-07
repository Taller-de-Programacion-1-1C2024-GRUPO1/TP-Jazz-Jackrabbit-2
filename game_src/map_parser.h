#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../physics_src/physical_map.h"

#include "constants_game.h"
#include "map.h"

class MapParser {

public:
    MapParser() = default;
    ~MapParser() = default;

    std::map<int, std::vector<SpawnPoint>> parse_spawn_points(
            std::map<int, int[MAP_WIDTH_DEFAULT][MAP_HEIGHT_DEFAULT]> map_data) {
        std::map<int, std::vector<SpawnPoint>> spawn_points;
        for (int x = 0; x < MAP_WIDTH_DEFAULT; x++) {
            for (int y = 0; y < MAP_HEIGHT_DEFAULT; y++) {
                switch (map_data[SPAWN_POINTS_LAYER][x][y]) {
                    case RABBIT_SPAWN:
                        spawn_points[RABBIT_SPAWN].push_back(SpawnPoint(x, y));
                        break;
                    case CRAB_SPAWN:
                        spawn_points[CRAB_SPAWN].push_back(SpawnPoint(x, y));
                        break;
                    case LIZARD_SPAWN:
                        spawn_points[LIZARD_SPAWN].push_back(SpawnPoint(x, y));
                        break;
                    case TURTLE_SPAWN:
                        spawn_points[TURTLE_SPAWN].push_back(SpawnPoint(x, y));
                        break;
                    case COIN_SPAWN:
                        spawn_points[COIN_SPAWN].push_back(SpawnPoint(x, y));
                        break;
                    case GEM_SPAWN:
                        spawn_points[GEM_SPAWN].push_back(SpawnPoint(x, y));
                        break;
                    default:
                        break;
                }
            }
        }
        return spawn_points;
    }

    void parse_physical_map(std::map<int, int[MAP_WIDTH_DEFAULT][MAP_HEIGHT_DEFAULT]> map_data,
                            PhysicalMap& physic_map) {
        if (map_data.empty()) {
            std::cout << "Map data is empty" << std::endl;
            return;
        }
        for (const auto& [current_layer, layer_data]: map_data) {
            switch (current_layer) {
                case DIAG_LEFT_LAYER:
                    override_layer(DIAG_LEFT_OBJ, layer_data, physic_map);
                    break;
                case DIAG_RIGHT_LAYER:
                    override_layer(DIAG_RIGHT_OBJ, layer_data, physic_map);
                    break;
                case COLLIDER_LAYER:
                    override_layer(COLLIDER_OBJ, layer_data, physic_map);
                    break;
                default:
                    break;
            }
        }
        // print physical map
        for (int y = 0; y < MAP_HEIGHT_DEFAULT; y++) {
            for (int x = 0; x < MAP_WIDTH_DEFAULT; x++) {
                std::cout << physic_map.map[x][y] << " ";
            }
            std::cout << std::endl;
        }
    }

    void override_layer(
            int layer_variable,
            const std::__tuple_element_t<
                    1UL, std::pair<const int, int[MAP_WIDTH_DEFAULT][MAP_HEIGHT_DEFAULT]>>
                    layer_data,
            PhysicalMap& physic_map) {
        for (int x = 0; x < MAP_WIDTH_DEFAULT; x++) {
            for (int y = 0; y < MAP_HEIGHT_DEFAULT; y++) {
                if (layer_data[x][y] != UNDEFINED) {
                    physic_map.map[x][y] = layer_variable;
                }
            }
        }
    }
};

#endif
