#include <cstdint>
#include <cstdlib>
#include <memory>
#include <thread>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "../common_src/common_errors.h"
#include "../common_src/common_socket.h"
#include "../common_src/constants.h"
#include "../game_src/map.h"
#include "../game_src/map_reader.h"


const char map_routes[] = "/etc/jazz/maps.txt";
const char map_nameTEST[] = "carrotus";
MapReader map_reader(map_routes);

const std::vector<std::vector<int>> map_data_TEST = {
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, 0,  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};

TEST(MapReaderTest, LoadMapsFilesMapNameTest) {

    std::map<std::string, Map> maps = map_reader.get_maps();

    EXPECT_EQ(maps[map_nameTEST].get_name(), map_nameTEST);
}

TEST(MapReaderTest, LoadMapsFilesDynamicMapTest) {
    std::map<std::string, Map> maps = map_reader.get_maps();

    std::map<int, int[MAP_WIDTH_DEFAULT][MAP_HEIGHT_DEFAULT]> map_data =
            maps[map_nameTEST].get_dynamic_map().map_data;

    // si se leen {x} cantidad de lineas y todas estan correctas, el resto de la matriz estará
    // correcto por construcción. se hace una adaptacion de matriz - vector de vectores para
    // comparar
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < MAP_WIDTH_DEFAULT; j++) {
            EXPECT_EQ(map_data[SPAWN_POINTS_LAYER][j][i], map_data_TEST[i][j]);
        }
    }
}

TEST(MapReaderTest, LoadMapsFilesSpawnPointsTest) {
    std::map<std::string, Map> maps = map_reader.get_maps();

    std::vector<SpawnPoint> spawn_points_vector =
            maps[map_nameTEST].get_spawn_points()[RABBIT_SPAWN];

    // si se leen {x} cantidad de lineas y todas estan correctas, el resto de la matriz estará
    // correcto por construcción. se hace una adaptacion de matriz - vector de vectores para
    // comparar
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < MAP_WIDTH_DEFAULT; j++) {
            if (map_data_TEST[i][j] != -1) {
                EXPECT_EQ(spawn_points_vector[0].get_x(), 2);
                EXPECT_EQ(spawn_points_vector[0].get_y(), 3);
            }
        }
    }
}
