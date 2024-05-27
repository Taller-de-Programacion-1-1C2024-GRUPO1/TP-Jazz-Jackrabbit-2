#ifndef CLIENT_WEAPON_INFO_H
#define CLIENT_WEAPON_INFO_H

#include <vector>
#include "SDL2pp/SDL2pp.hh"

class WeaponInfo {
private:
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture weaponTexture;
    std::vector<SDL2pp::Rect> weaponRects;
    int currentWeapon;
    int currentAmmo;

public:
    WeaponInfo(SDL2pp::Renderer& renderer);
    void loadWeapons();
    void setWeapon(int weapon);
    void setAmmo(int ammo);
    void render();
};

#endif //CLIENT_WEAPON_INFO_H