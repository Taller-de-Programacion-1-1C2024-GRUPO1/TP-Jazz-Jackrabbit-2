#ifndef CLIENT_DRAWABLE_AMMO_H
#define CLIENT_DRAWABLE_AMMO_H

#include "client_shifting_drawable.h"
#include "client_textures_provider.h"

class DrawableAmmo: public ShiftingDrawable {
public:
    DrawableAmmo(SDL2pp::Renderer& renderer, SDL2pp::Point& cp, SDL2pp::Rect& textureRect,
                 SDL2pp::Rect& onMapRect, SoundManager& soundManager):
            ShiftingDrawable(renderer, cp, textureRect, onMapRect, soundManager) {}

    void setAmmoFromSnapshot(const int ammo_type) {
        switch (ammo_type) {
            case SNIPER_AMMO:
                this->loadAnimations(ROCKET_LAUCHER_ANIMATIONS);
                this->setTexture(TexturesProvider::getTexture("Items"));
                break;
            case MACHINEGUN_AMMO:
                this->loadAnimations(MACHINE_GUN_ANIMATIONS);
                this->setTexture(TexturesProvider::getTexture("Projectiles"));
                break;
            case RAYGUN_AMMO:
                this->loadAnimations(RAY_GUN_ANIMATIONS);
                this->setTexture(TexturesProvider::getTexture("Projectiles"));
                break;
            default:
                throw std::invalid_argument("Invalid ammo type");
        }
    }

    void playSoundOnDeath() override { this->soundManager.playSoundEffect("Ammo-Pickup"); }
};

#endif  // CLIENT_DRAWABLE_AMMO_H
