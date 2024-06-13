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
    explicit MapReader(const std::string& filePath = ""): file_path(filePath) { load_maps_files(); }

    ~MapReader() {}

    void get_maps(std::map<std::string, Map>& dicc_maps) { set_maps(dicc_maps); }

    void refresh_load_maps(std::map<std::string, Map>& dicc_maps) {
        load_maps_files();
        set_maps(dicc_maps);
    }

private:
    std::string file_path;
    std::vector<std::string> map_paths;
    MapParser map_parser;

    void load_maps_files() {
        std::ifstream file(file_path);
        std::string line;
        map_paths.clear();
        if (file.is_open()) {
            while (std::getline(file, line)) {
                map_paths.push_back(BASE_MAPS_PATH + line);
                std::cout << "Map file: " << line << std::endl;
            }
            file.close();
        } else {
            throw std::runtime_error("Error opening maps file: " + file_path);
        }
    }

    void set_maps(std::map<std::string, Map>& dicc_maps) {
        for (const auto& map_path: map_paths) {
            load_map(map_path, dicc_maps);
        }
    }

    void load_map(const std::string& map_path, std::map<std::string, Map>& dicc_maps) {
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

            map_parser.parse_maps(game_map_name, width, height, max_players, texture_id, map_data,
                                  dicc_maps);

        } catch (const YAML::BadFile& e) {
            throw std::runtime_error("Error reading map file: " + file_path);
        }
    }
};


#endif
