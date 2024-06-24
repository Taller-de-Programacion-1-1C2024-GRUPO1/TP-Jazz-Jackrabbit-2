#ifndef CLIENT_WEAPON_INFO_H
#define CLIENT_WEAPON_INFO_H

#include <memory>
#include <vector>

#include "../game_src/constants_game.h"
#include "SDL2pp/SDL2pp.hh"

#include "client_constants.h"
#include "client_fonts_printer.h"
#include "client_textures_provider.h"

class AmmoLeft {
private:
    SDL2pp::Renderer& renderer;
    SDL2pp::Rect munitionRect;
    std::shared_ptr<SDL2pp::Texture> munitionTexture;
    int currentWeapon;
    int currentAmmo;
    FontPrinter fontPrinter;

public:
    explicit AmmoLeft(SDL2pp::Renderer& renderer);
    void setWeapon(int weapon);
    void setAmmo(int ammo);
    void render();
};

#endif  // CLIENT_WEAPON_INFO_H
