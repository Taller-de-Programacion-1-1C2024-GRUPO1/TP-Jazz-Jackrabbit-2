#ifndef CLIENT_VALUABLE_H
#define CLIENT_VALUABLE_H

#include "client_shifting_drawable.h"
#include "client_textures_provider.h"

class DrawableValuable: public ShiftingDrawable {

public:
    DrawableValuable(SDL2pp::Renderer& renderer, SDL2pp::Point& cp, SDL2pp::Rect& textureRect,
                     SDL2pp::Rect& onMapRect, SoundManager& soundManager):
            ShiftingDrawable(renderer, cp, textureRect, onMapRect, soundManager) {}

    void setValuableFromSnapshot(const int valuable_type) {
        this->setTexture(TexturesProvider::getTexture("Items"));
        switch (valuable_type) {
            case COIN:
                this->loadAnimations(COIN_ANIMATIONS);
                break;
            case GEM:
                this->loadAnimations(GEM_ANIMATIONS);
                break;
        }
    }

    void playSoundOnDeath() override { soundManager.playSoundEffect("Coin-Pickup"); }
};

#endif  // CLIENT_VALUABLE_H
