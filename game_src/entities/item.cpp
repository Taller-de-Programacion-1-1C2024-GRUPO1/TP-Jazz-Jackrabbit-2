#include "item.h"

#include "rabbit.h"

Item::Item(int init_pos_x, int init_pos_y):
        PhysicalObject(BLOCK_DIVISION, BLOCK_DIVISION, init_pos_x, init_pos_y) {}

Ammo::Ammo(int init_pos_x, int init_pos_y): Item(init_pos_x, init_pos_y) {}

Gem::Gem(int init_pos_x, int init_pos_y): Item(init_pos_x, init_pos_y) {}

Coin::Coin(int init_pos_x, int init_pos_y): Item(init_pos_x, init_pos_y) {}

void Coin::on_colision_with_rabbit(Rabbit* rabbit) {
    rabbit->add_points(COIN_POINTS);
    kill();
}

void Gem::on_colision_with_rabbit(Rabbit* rabbit) {
    rabbit->add_points(GEM_POINTS);
    kill();
}
