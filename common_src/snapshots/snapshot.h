#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <map>
#include <string>
#include <vector>

#include "../constants.h"
#include "../game_src/constants_game.h"
#include "../server_src/config.h"

// #include "snapshot_map.h" ???
#include "snapshot_projectile.h"
#include "snapshot_rabbit.h"
#include "snapshot_supply.h"

struct MapDimensions {
    int height = MAP_HEIGHT_DEFAULT;
    int width = MAP_WIDTH_DEFAULT;
    int rabbit_amount = RABBIT_AMOUNT_DEFAULT;
    int rabbit_width = RABBIT_WIDTH_DEFAULT;
    int rabbit_height = RABBIT_HEIGHT_DEFAULT;
} typedef MapDimensions_t;

class Snapshot {
    bool end_game = false;

public:
    /*
     * El snapshot tiene un vector de conejos, proyectiles y suministros
     * que se envian al cliente para que pueda renderizarlos en su pantalla
     * Además, tiene las dimensiones del mapa para que el cliente pueda renderizarlo correctamente
     */
    std::vector<RabbitSnapshot> rabbits;
    std::vector<ProjectileSnapshot> projectiles;
    std::vector<SupplySnapshot> supplies;
    MapDimensions_t map_dimensions;

    Snapshot(const std::vector<RabbitSnapshot>& rabbits,
             const std::vector<ProjectileSnapshot>& projectiles,
             const std::vector<SupplySnapshot>& supplies):
            rabbits(rabbits), projectiles(projectiles), supplies(supplies), map_dimensions() {}


    Snapshot() {}
    ~Snapshot() {}

    /*
     * Probablemente se use en un futuro para setear las dimensiones del mapa iniciales
     * Cuando se conecta un cliente, se le envía un snapshot con las dimensiones del mapa inicial
     * para que pueda renderizarlo correctamente en su pantalla
     */
    void set_dimensions(int height = 0, int width = 0, int rabbit_width = RABBIT_WIDTH_DEFAULT,
                        int rabbit_ammount = RABBIT_AMOUNT_DEFAULT,
                        int rabbit_height = RABBIT_HEIGHT_DEFAULT) {
        map_dimensions.height = height;
        map_dimensions.width = width;
        map_dimensions.rabbit_amount = rabbit_ammount;
        map_dimensions.rabbit_width = rabbit_width;
        map_dimensions.rabbit_height = rabbit_height;
    }

    void set_end_game() { end_game = true; }

    bool get_end_game() { return end_game; }
};

#endif
