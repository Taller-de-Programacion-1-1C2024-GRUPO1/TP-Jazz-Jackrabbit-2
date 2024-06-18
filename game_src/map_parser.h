#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "constants_game.h"
#include "map.h"

class MapParser {

public:
    MapParser() = default;
    ~MapParser() = default;

    void parse_maps(std::string map_name, int width, int height, int max_players, int texture,
                    const std::map<int, std::vector<std::vector<int>>>& map_data,
                    std::map<std::string, Map>& maps) {

        std::map<int, std::vector<SpawnPoint>> spawn_points =
                parse_spawn_points(width, height, map_data);

        PhysicalMap physical_map = parse_physical_map(width, height, map_data);

        DynamicMap dynamic_map = DynamicMap(width, height, map_data);

        Map map = Map(width, height, texture, max_players, map_name, physical_map, dynamic_map,
                      spawn_points);

        maps[map_name] = map;
    }

    std::map<int, std::vector<SpawnPoint>> parse_spawn_points(
            int width, int height, std::map<int, std::vector<std::vector<int>>> map_data) {
        std::map<int, std::vector<SpawnPoint>> spawn_points;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
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

    PhysicalMap parse_physical_map(int width, int height,
                                   std::map<int, std::vector<std::vector<int>>> map_data) {

        std::vector<std::vector<int>> physic_map(width, std::vector<int>(height, 0));

        for (const auto& [current_layer, layer_data]: map_data) {
            switch (current_layer) {
                case DIAG_LEFT_LAYER:
                    for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                            if (layer_data[x][y] != UNDEFINED) {
                                physic_map[x][y] = DIAG_LEFT_OBJ;
                            }
                        }
                    }
                    break;
                case DIAG_RIGHT_LAYER:
                    for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                            if (layer_data[x][y] != UNDEFINED) {
                                physic_map[x][y] = DIAG_RIGHT_OBJ;
                            }
                        }
                    }
                    break;
                case COLLIDER_LAYER:
                    for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                            if (layer_data[x][y] != UNDEFINED) {
                                physic_map[x][y] = COLLIDER_OBJ;
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        PhysicalMap physical_map = PhysicalMap(width, height, physic_map);

        // print map
        /*
        std::cout << "PRINTING MAP..." << std::endl;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                std::cout << physical_map.map[x][y] << " ";
            }
            std::cout << std::endl;
        }
        */

        return physical_map;
    }
};

#endif
