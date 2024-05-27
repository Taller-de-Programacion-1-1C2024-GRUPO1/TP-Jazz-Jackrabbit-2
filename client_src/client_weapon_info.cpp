#include "client_weapon_info.h"
#include "client_number_images.h"

#define WEAPONS_IMG "../client_src/resources/items/items.png"

WeaponInfo::WeaponInfo(SDL2pp::Renderer& renderer)
    : renderer(renderer), weaponTexture(renderer, WEAPONS_IMG), currentWeapon(0), currentAmmo(1000) {
    SDL2pp::Surface surface(WEAPONS_IMG);
    SDL_Color colorKey = {0, 128, 255, 1};
    SDL_SetColorKey(surface.Get(), SDL_TRUE,
                    SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b));
    this->weaponTexture = SDL2pp::Texture(renderer, surface);
    loadWeapons();
}

void WeaponInfo::loadWeapons(){
    weaponRects.push_back(SDL2pp::Rect(69, 26, 22, 26));
    weaponRects.push_back(SDL2pp::Rect(70, 57, 18, 21));
    weaponRects.push_back(SDL2pp::Rect(9, 395, 32, 23));
}

void WeaponInfo::setWeapon(int weapon) {
    this->currentWeapon = weapon;
}

void WeaponInfo::setAmmo(int ammo) {
    this->currentAmmo = ammo;
}


void WeaponInfo::render() {
    NumberImages numberImages(renderer);

    std::string ammoStr = std::to_string(currentAmmo);
    std::reverse(ammoStr.begin(), ammoStr.end()); // Invert the string
    int offset = 64; // Start position

    for (char c : ammoStr) {
        int number = c - '0'; // Convert char to int
        numberImages.renderNumber(number,offset);
        offset += 24; // Move position to the left for the next digit
    }

    SDL2pp::Rect currentRect(800 - offset, 600 - 32, 32, 32);
    renderer.Copy(weaponTexture, weaponRects[currentWeapon], currentRect);
}