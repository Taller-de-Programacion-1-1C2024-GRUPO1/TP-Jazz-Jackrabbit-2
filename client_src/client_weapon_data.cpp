#include "client_weapon_data.h"

std::map<int, SDL2pp::Rect> WeaponData::weaponMap;

void WeaponData::initialize() {
    weaponMap[0] = SDL2pp::Rect(69, 26, 22, 26);   // arma inicial azul
    weaponMap[1] = SDL2pp::Rect(70, 57, 18, 21);   // arma inicial verde
    weaponMap[2] = SDL2pp::Rect(66, 135, 22, 15);  // bolita violeta
    weaponMap[3] = SDL2pp::Rect(66, 152, 22, 15);  // bolita celeste
    weaponMap[4] = SDL2pp::Rect(91, 322, 18, 17);  // bombita violeta
    weaponMap[5] = SDL2pp::Rect(91, 341, 18, 17);  // bombita roja
}

SDL2pp::Rect WeaponData::getWeapon(int id) { return weaponMap[id]; }

void WeaponData::loadAnimationsToProjectile(int id, ShiftingDrawable* projectile) {
    switch (id) {
        case BASIC_GUN:
            projectile->loadAnimations("../external/animations/projectiles/regular.yml");
            break;
        case MACHINE_GUN:
            projectile->loadAnimations("../external/animations/projectiles/blue_ray.yml");
            break;
        case SNIPER:
            projectile->loadAnimations("../external/animations/projectiles/blue_ray.yml");
            break;
    }
}
