#ifndef CLIENT_WEAPON_INFO_H
#define CLIENT_WEAPON_INFO_H

#include <vector>

#include "../game_src/constants_game.h"
#include "SDL2pp/SDL2pp.hh"

#include "client_number_images.h"
#include "client_constants.h"

class AmmoLeft {
private:
    SDL2pp::Renderer& renderer;
    SDL2pp::Rect munitionRect;
    SDL2pp::Texture munitionTexture;
    int currentWeapon;
    int currentAmmo;
    NumberImages numberImages;

public:
    explicit AmmoLeft(SDL2pp::Renderer& renderer);
    void loadWeapons();
    void setWeapon(int weapon);
    void setAmmo(int ammo);
    void render();
};

#endif  // CLIENT_WEAPON_INFO_H
