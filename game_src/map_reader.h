#ifndef MAP_READER_H
#define MAP_READER_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "../game_src/dynamic_map.h"
#include "../game_src/map.h"
#include "../physics_src/physical_map.h"

#include "map_parser.h"

#define BASE_MAPS_PATH "/var/jazz/maps/"

class MapReader {
public:
    std::string file_path;
    MapParser map_parser;

    explicit MapReader(const std::string& filePath = ""): file_path(filePath) {}

    ~MapReader() = default;

    std::vector<std::string> load_maps_files() {
        std::vector<std::string> map_paths;
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
        return map_paths;
    }

    std::shared_ptr<Map> load_map(const std::string& map_path) {
        if (map_path.empty()) {
            throw std::runtime_error("Maps file path is not set");
        }
        if (!std::filesystem::exists(map_path)) {
            throw std::runtime_error("Maps file does not exist: " + map_path);
        }
        try {
            std::cout << "Reading map: " << map_path << std::endl;
            YAML::Node map = YAML::LoadFile(map_path);
            std::map<int, int[MAP_WIDTH_DEFAULT][MAP_HEIGHT_DEFAULT]> map_data;
            
            for (const auto& node: map["layers"]) {
                int id = node["id"].as<int>();
                const YAML::Node& data = node["data"];
                if (data.IsSequence()) {
                    for (std::size_t i = 0; i < data.size(); ++i) {
                        const YAML::Node& fila = data[i];
                        for (std::size_t j = 0; j < fila.size(); ++j) {
                            const YAML::Node& valor = fila[j];
                            map_data[id][j][i] = valor.as<int>();
                        }
                    }
                }
            }

            Map game_map = Map();

            std::string game_map_name = map["name"].as<std::string>();
            game_map.set_name(game_map_name);
            
            // cargo el mapa fisico
            PhysicalMap physical_map = PhysicalMap();
            map_parser.parse_physical_map(map_data, physical_map);
            game_map.set_physical_map(std::move(physical_map));

            // cargo los spawn points
            game_map.set_spawn_points(map_parser.parse_spawn_points(map_data));

            // cargo el mapa dinamico
            DynamicMap dynamic_map = DynamicMap(map_data);
            game_map.set_dynamic_map(std::move(dynamic_map));

            game_map.set_max_players(map["max_players"].as<int>());

            return std::make_shared<Map>(std::move(game_map));

        } catch (const YAML::BadFile& e) {
            throw std::runtime_error("Error reading map file: " + file_path);
        }
    }
};

#endif
