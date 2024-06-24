#include "item.h"

#include "../constants_game.h"

#include "rabbit.h"

Item::Item(int id, int type, int init_pos_x, int init_pos_y):
        id(id),
        type(type),
        PhysicalObject(BLOCK_DIVISION, BLOCK_DIVISION, init_pos_x, init_pos_y) {}

MachineGunAmmo::MachineGunAmmo(int id, int init_pos_x, int init_pos_y):
        Item(id, MACHINEGUN_AMMO, init_pos_x, init_pos_y) {}

SniperAmmo::SniperAmmo(int id, int init_pos_x, int init_pos_y):
        Item(id, SNIPER_AMMO, init_pos_x, init_pos_y) {}

RayGunAmmo::RayGunAmmo(int id, int init_pos_x, int init_pos_y):
        Item(id, RAYGUN_AMMO, init_pos_x, init_pos_y) {}


Gem::Gem(int id, int init_pos_x, int init_pos_y): Item(id, GEM, init_pos_x, init_pos_y) {}

Coin::Coin(int id, int init_pos_x, int init_pos_y): Item(id, COIN, init_pos_x, init_pos_y) {}

void Coin::on_colision_with_rabbit(Rabbit* rabbit) {
    rabbit->add_points(COIN_POINTS);
    kill();
}

void Gem::on_colision_with_rabbit(Rabbit* rabbit) {
    rabbit->add_points(GEM_POINTS);
    kill();
}
void MachineGunAmmo::on_colision_with_rabbit(Rabbit* rabbit) {
    rabbit->add_machinegun_ammo(FLAMETHROWER_AMMO_AMOUNT);
    kill();
}
void SniperAmmo::on_colision_with_rabbit(Rabbit* rabbit) {
    rabbit->add_sniper_ammo(ROCKETLAUNCHER_AMMO_AMOUNT);
    kill();
}
void RayGunAmmo::on_colision_with_rabbit(Rabbit* rabbit) {
    rabbit->add_raygun_ammo(RAYGUN_AMMO_AMOUNT);
    kill();
}


HealthCarrot::HealthCarrot(int id, int init_pos_x, int init_pos_y):
        Item(id, HEALTH_CARROT, init_pos_x, init_pos_y) {}

Hotdog::Hotdog(int id, int init_pos_x, int init_pos_y): Item(id, HOTDOG, init_pos_x, init_pos_y) {}

Hamburger::Hamburger(int id, int init_pos_x, int init_pos_y):
        Item(id, HAMBURGER, init_pos_x, init_pos_y) {}

RottenCheese::RottenCheese(int id, int init_pos_x, int init_pos_y):
        Item(id, ROTTEN_CHEESE, init_pos_x, init_pos_y) {}

void HealthCarrot::on_colision_with_rabbit(Rabbit* rabbit) {
    rabbit->add_health(CARROT_HEALTH_AMOUNT);
    kill();
}
void Hotdog::on_colision_with_rabbit(Rabbit* rabbit) {
    rabbit->add_points(HOTDOG_POINTS_AMOUNT);
    kill();
}
void Hamburger::on_colision_with_rabbit(Rabbit* rabbit) {
    rabbit->add_points(HAMBURGER_POINTS_AMOUNT);
    kill();
}
void RottenCheese::on_colision_with_rabbit(Rabbit* rabbit) {
    rabbit->set_intoxicated();
    kill();
}


SupplySnapshot Item::get_snapshot() { return SupplySnapshot(id, type, pos_x, pos_y); }
