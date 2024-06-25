#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <map>
#include <string>
#include <vector>

#include "../../client_src/client_constants.h"
#include "../../game_src/constants_game.h"
#include "../../game_src/dynamic_map.h"
#include "../../server_src/config.h"
#include "../constants.h"

#include "snapshot_enemy.h"
#include "snapshot_projectile.h"
#include "snapshot_rabbit.h"
#include "snapshot_supply.h"

struct MapDimensions {
    int height = MAP_HEIGHT_DEFAULT;
    int width = MAP_WIDTH_DEFAULT;
    int rabbit_amount = RABBIT_AMOUNT_DEFAULT;
    int rabbit_width = RABBIT_WIDTH_DEFAULT;
    int rabbit_height = RABBIT_HEIGHT_DEFAULT;
    DynamicMap map_data = {};
    int map_texture_id = CARROTUS;
} typedef MapDimensions_t;

class Snapshot {
    bool end_game = false;
    uint32_t match_time = 0;

public:
    /*
     * El snapshot tiene un vector de conejos, enemigos, proyectiles y suministros
     * que se envian al cliente para que pueda renderizarlos en su pantalla
     * Además, tiene las dimensiones del mapa para que el cliente pueda renderizarlo correctamente
     */
    std::vector<RabbitSnapshot> rabbits;
    std::vector<EnemySnapshot> enemies;
    std::vector<ProjectileSnapshot> projectiles;
    std::vector<SupplySnapshot> supplies;
    MapDimensions_t map_dimensions;

    Snapshot(const std::vector<RabbitSnapshot>& rabbits, const std::vector<EnemySnapshot>& enemies,
             const std::vector<ProjectileSnapshot>& projectiles,
             const std::vector<SupplySnapshot>& supplies):
            rabbits(rabbits),
            enemies(enemies),
            projectiles(projectiles),
            supplies(supplies),
            map_dimensions() {}

    Snapshot() {}
    ~Snapshot() {}

    void set_dimensions(int height = 0, int width = 0, int rabbit_width = RABBIT_WIDTH_DEFAULT,
                        int rabbit_height = RABBIT_HEIGHT_DEFAULT,
                        int rabbit_ammount = RABBIT_AMOUNT_DEFAULT, const DynamicMap& map_data = {},
                        int texture = 0) {

        map_dimensions.height = height;
        map_dimensions.width = width;
        map_dimensions.rabbit_amount = rabbit_ammount;
        map_dimensions.rabbit_width = rabbit_width;
        map_dimensions.rabbit_height = rabbit_height;
        map_dimensions.map_data = map_data;
        map_dimensions.map_texture_id = texture;
    }

    void set_end_game() { this->end_game = true; }

    bool get_end_game() { return end_game; }

    void set_match_time(uint32_t match_time) { this->match_time = match_time; }
    uint32_t get_match_time() { return match_time; }
};

#endif
