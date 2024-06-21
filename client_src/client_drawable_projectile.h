#ifndef CLIENT_DRAWABLE_PROJECTILE_H
#define CLIENT_DRAWABLE_PROJECTILE_H

#include "client_constants.h"
#include "client_shifting_drawable.h"
#include "client_textures_provider.h"

class DrawableProjectile: public ShiftingDrawable {
private:
    bool requires_explosion = false;
    bool is_exploding = false;
    int explosion_frames = 5 * 4;

public:
    DrawableProjectile(SDL2pp::Renderer& renderer, SDL2pp::Point& cp, SDL2pp::Rect& textureRect,
                       SDL2pp::Rect& onMapRect, SoundManager& soundManager):
            ShiftingDrawable(renderer, cp, textureRect, onMapRect, soundManager) {}

    void setProjectileFromSnapshot(const int projectile_type) {
        this->setTexture(TexturesProvider::getTexture("Projectiles"));
        switch (projectile_type) {
            case BASIC_GUN:
                this->loadAnimations(REGULAR_ANIMATIONS);
                break;
            case FLAMETHROWER:
                this->loadAnimations(BLUE_RAY_ANIMATIONS);
                break;
            case ROCKETLAUNCHER:
                this->loadAnimations(ROCKET_ANIMATIONS);
                this->requires_explosion = true;
                this->is_exploding = true;
                break;
            case RAYGUN:
                this->loadAnimations(RAY_ANIMATIONS);
                this->requires_explosion = true;
                this->is_exploding = true;
                break;
            default:
                throw std::invalid_argument("Invalid projectile type");
        }
    }

    void setRequiresExplosion(bool requires_explosion) { this->requires_explosion = false; }

    void keepExploding() {
        explosion_frames--;
        if (explosion_frames == 0) {
            this->is_exploding = false;
        }
    }

    bool requiresExplosion() { return requires_explosion; }

    bool isExploding() { return is_exploding; }

    void playSoundOnDeath() override { soundManager.playSoundEffect("Explosion"); }
};


#endif  // CLIENT_DRAWABLE_PROJECTILE_H
