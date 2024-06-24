#ifndef MAP_READER_H
#define MAP_READER_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "../game_src/dynamic_map.h"
#include "../game_src/map.h"
#include "../physics_src/physical_map.h"

#define BASE_MAPS_PATH "/var/jazz/maps/"


class MapReader {
public:
    explicit MapReader(const std::string& filePath = ""): file_path(filePath) { load_maps_files(); }

    ~MapReader() {}

    void get_maps(std::map<std::string, std::shared_ptr<Map>>& dicc_maps) { set_maps(dicc_maps); }

    void refresh_load_maps(std::map<std::string, std::shared_ptr<Map>>& dicc_maps) {
        load_maps_files();
        set_maps(dicc_maps);
    }

private:
    std::string file_path;
    std::vector<std::string> map_paths;

    void load_maps_files() {
        std::ifstream file(file_path);
        std::string line;
        map_paths.clear();
        if (file.is_open()) {
            while (std::getline(file, line)) {
                map_paths.push_back(BASE_MAPS_PATH + line);
            }
            file.close();
        } else {
            throw std::runtime_error("Error opening maps file: " + file_path);
        }
    }

    void set_maps(std::map<std::string, std::shared_ptr<Map>>& dicc_maps) {
        for (const auto& map_path: map_paths) {
            std::cout << "Loading map: " << map_path << std::endl;
            load_map(map_path, dicc_maps);
        }
    }

    void load_map(const std::string& map_path,
                  std::map<std::string, std::shared_ptr<Map>>& dicc_maps) {
        if (map_path.empty()) {
            throw std::runtime_error("Maps file path is not set");
        }
        if (!std::filesystem::exists(map_path)) {
            throw std::runtime_error("Maps file does not exist: " + map_path);
        }
        try {
            YAML::Node map = YAML::LoadFile(map_path);

            std::string game_map_name = map["name"].as<std::string>();
            int max_players = map["max_players"].as<int>();
            int texture_id = map["texture"].as<int>();
            int width = map["width"].as<int>();
            int height = map["height"].as<int>();

            std::map<int, std::vector<std::vector<int>>> map_data;

            for (const auto& node: map["layers"]) {
                int id = node["id"].as<int>();
                const YAML::Node& data = node["data"];
                if (data.IsSequence()) {
                    map_data[id] =
                            std::vector<std::vector<int>>(width, std::vector<int>(height, 0));
                    // printea la matriz
                    for (std::size_t y = 0; y < data.size(); ++y) {
                        const YAML::Node& fila = data[y];
                        for (std::size_t x = 0; x < fila.size(); ++x) {
                            const YAML::Node& valor = fila[x];
                            map_data[id][x][y] = valor.as<int>();
                        }
                    }
                }
            }

            dicc_maps[game_map_name] =
                    std::make_shared<Map>(width, height, texture_id, max_players, game_map_name,
                                          parse_physical_map(width, height, map_data),
                                          DynamicMap(width, height, map_data),
                                          parse_spawn_points(width, height, map_data));
        } catch (const YAML::BadFile& e) {
            throw std::runtime_error("Error reading map file: " + file_path);
        }
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
