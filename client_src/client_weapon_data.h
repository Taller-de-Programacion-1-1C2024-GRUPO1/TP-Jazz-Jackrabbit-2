#ifndef CLIENT_WEAPON_DATA_H
#define CLIENT_WEAPON_DATA_H

#include <map>

#include "SDL2pp/SDL2pp.hh"

#include "client_shifting_drawable.h"

class WeaponData {
private:
    static std::map<int, SDL2pp::Rect> weaponMap;

public:
    static void initialize();
    static SDL2pp::Rect getWeapon(int id);
    static void loadAnimationsToProjectile(int id, ShiftingDrawable* projectile);
};


#endif  // CLIENT_WEAPON_DATA_H
