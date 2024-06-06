#include "item.h"

#include "../constants_game.h"

#include "rabbit.h"

Item::Item(int id, int type, int init_pos_x, int init_pos_y):
        id(id),
        type(type),
        PhysicalObject(BLOCK_DIVISION, BLOCK_DIVISION, init_pos_x, init_pos_y) {}

Ammo::Ammo(int id, int init_pos_x, int init_pos_y): Item(id, AMMO, init_pos_x, init_pos_y) {}

Gem::Gem(int id, int init_pos_x, int init_pos_y): Item(id, GEM, init_pos_x, init_pos_y) {}

Coin::Coin(int id, int init_pos_x, int init_pos_y):
        Item(id, COIN, init_pos_x * BLOCK_DIVISION, init_pos_y * BLOCK_DIVISION) {}

void Coin::on_colision_with_rabbit(Rabbit* rabbit) {
    rabbit->add_points(COIN_POINTS);
    kill();
}

void Gem::on_colision_with_rabbit(Rabbit* rabbit) {
    rabbit->add_points(GEM_POINTS);
    kill();
}

SupplySnapshot Item::get_snapshot() { return SupplySnapshot(id, type, pos_x, pos_y); }
