#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "../physics_src/physical_map.h"

#include "constants_game.h"
#include "map.h"

class MapParser {

public:
    MapParser() = default;
    ~MapParser() = default;

    void parse_physical_map(std::map<int, int[MAP_WIDTH_DEFAULT][MAP_HEIGHT_DEFAULT]> map_data,
                            PhysicalMap& physic_map) {
        for (const auto& [current_layer, layer_data]: map_data) {
            if (current_layer == DIAG_LEFT_LAYER) {
                for (int x = 0; x < MAP_WIDTH_DEFAULT; x++) {
                    for (int y = 0; y < MAP_HEIGHT_DEFAULT; y++) {
                        if (layer_data[x][y] == UNDEFINED) {
                            physic_map.map[x][y] = NULL_OBJ;
                        } else {
                            physic_map.map[x][y] = DIAG_LEFT_OBJ;
                        }
                    }
                }
            } else if (current_layer == DIAG_RIGHT_LAYER) {
                for (int x = 0; x < MAP_WIDTH_DEFAULT; x++) {
                    for (int y = 0; y < MAP_HEIGHT_DEFAULT; y++) {
                        if (layer_data[x][y] == UNDEFINED) {
                            physic_map.map[x][y] = NULL_OBJ;
                        } else {
                            physic_map.map[x][y] = DIAG_RIGHT_OBJ;
                        }
                    }
                }
            } else if (current_layer == COLLIDER_LAYER) {
                for (int x = 0; x < MAP_WIDTH_DEFAULT; x++) {
                    for (int y = 0; y < MAP_HEIGHT_DEFAULT; y++) {
                        if (layer_data[x][y] == UNDEFINED) {
                            physic_map.map[x][y] = NULL_OBJ;
                        } else {
                            physic_map.map[x][y] = COLLIDER_OBJ;
                        }
                    }
                }
            } else if (current_layer == SPAWN_POINTS_LAYER) {
                for (int x = 0; x < MAP_WIDTH_DEFAULT; x++) {
                    for (int y = 0; y < MAP_HEIGHT_DEFAULT; y++) {
                        if (layer_data[x][y] != UNDEFINED) {
                            physic_map.spawn_points.push_back(SpawnPoint(x, y));
                        }
                    }
                }
            }
        }
    }
};

#endif
