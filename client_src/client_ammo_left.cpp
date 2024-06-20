#include "client_ammo_left.h"

#include <string>

AmmoLeft::AmmoLeft(SDL2pp::Renderer& renderer):
        renderer(renderer),
        munitionRect(69, 26, 22, 26),  // BASIC GUN
        munitionTexture(TexturesProvider::getTexture("Items")),
        currentWeapon(0),
        currentAmmo(1000),
        numberImages(renderer) {}

void AmmoLeft::setWeapon(int weapon_type) {
    switch (weapon_type) {
        case BASIC_GUN:
            munitionRect = SDL2pp::Rect(69, 26, 22, 26);
            break;
        case MACHINE_GUN:
            munitionRect = SDL2pp::Rect(66, 152, 22, 15);
            break;
        case SNIPER:
            munitionRect = SDL2pp::Rect(112, 220, 21, 24);
            break;
        case RAYGUN:
            munitionRect = SDL2pp::Rect(485, 410, 18, 17);
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
    offset -= 24;  // Move position to the left for the munition icon
    SDL2pp::Rect currentRect(800 + offset - BLOCK_DIVISION, 600 - BLOCK_DIVISION, BLOCK_DIVISION,
                             BLOCK_DIVISION);
    renderer.Copy(*munitionTexture, munitionRect, currentRect);
}
