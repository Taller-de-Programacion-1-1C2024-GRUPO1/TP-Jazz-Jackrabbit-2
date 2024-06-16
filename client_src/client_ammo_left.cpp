#include "client_ammo_left.h"

#include <string>

AmmoLeft::AmmoLeft(SDL2pp::Renderer& renderer):
        renderer(renderer),
        munitionRect(69, 26, 22, 26),  // BASIC GUN
        munitionTexture(renderer, SDL2pp::Surface(ITEMS_PNG)),
        currentWeapon(0),
        currentAmmo(1000),
        numberImages(renderer) {
    SDL2pp::Surface surface(ITEMS_PNG);
    SDL_Color colorKey = {0, 128, 255, 1};
    SDL_SetColorKey(surface.Get(), SDL_TRUE,
                    SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b));
    this->munitionTexture = SDL2pp::Texture(renderer, surface);
}

void AmmoLeft::setWeapon(int weapon_type) {
    switch (weapon_type) {
        case BASIC_GUN:
            munitionRect = SDL2pp::Rect(69, 26, 22, 26);
            break;
        case MACHINE_GUN:
            munitionRect = SDL2pp::Rect(91, 341, 18, 17);
            break;
        case SNIPER:
            munitionRect = SDL2pp::Rect(66, 152, 22, 15);
            break;
    }
}

void AmmoLeft::setAmmo(int ammo) { this->currentAmmo = ammo; }

void AmmoLeft::render() {
    std::string ammoStr = std::to_string(currentAmmo);
    std::reverse(ammoStr.begin(), ammoStr.end());  // Invert the string
    int offset = -64;                              // Start position
    numberImages.setCorner(1);                     // Set position to bottom right

    for (char c: ammoStr) {
        int number = c - '0';  // Convert char to int
        numberImages.renderNumber(number, offset, 0, 32);
        offset -= 24;  // Move position to the left for the next digit
    }
    numberImages.renderNumber(10, offset, 0, 32);  // Render X for ammo
    offset -= 24;                              // Move position to the left for the munition icon
    SDL2pp::Rect currentRect(800 + offset - BLOCK_DIVISION, 600 - BLOCK_DIVISION, BLOCK_DIVISION,
                             BLOCK_DIVISION);
    renderer.Copy(munitionTexture, munitionRect, currentRect);
}
