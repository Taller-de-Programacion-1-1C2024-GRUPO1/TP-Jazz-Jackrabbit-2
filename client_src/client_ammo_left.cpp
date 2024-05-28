#include "client_ammo_left.h"

#include <string>

#include "client_number_images.h"
#include "client_weapon_data.h"

#define WEAPONS_IMG "../client_src/resources/items/items.png"

AmmoLeft::AmmoLeft(SDL2pp::Renderer& renderer):
        renderer(renderer),
        weaponTexture(renderer, WEAPONS_IMG),
        currentWeapon(0),
        currentAmmo(1000) {
    SDL2pp::Surface surface(WEAPONS_IMG);
    SDL_Color colorKey = {0, 128, 255, 1};
    SDL_SetColorKey(surface.Get(), SDL_TRUE,
                    SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b));
    this->weaponTexture = SDL2pp::Texture(renderer, surface);
}

void AmmoLeft::setWeapon(int weapon) { this->currentWeapon = weapon; }

void AmmoLeft::setAmmo(int ammo) { this->currentAmmo = ammo; }

void AmmoLeft::render() {
    NumberImages numberImages(renderer);

    std::string ammoStr = std::to_string(currentAmmo);
    std::reverse(ammoStr.begin(), ammoStr.end());  // Invert the string
    int offset = -64;                              // Start position
    numberImages.setCorner(1);                     // Set position to bottom right

    for (char c: ammoStr) {
        int number = c - '0';  // Convert char to int
        numberImages.renderNumber(number, offset);
        offset -= 24;  // Move position to the left for the next digit
    }

    SDL2pp::Rect currentRect(800 + offset - 32, 600 - 32, 32, 32);
    renderer.Copy(weaponTexture, WeaponData::getWeapon(currentWeapon), currentRect);
}
