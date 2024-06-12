#ifndef CLIENT_VALUABLE_H
#define CLIENT_VALUABLE_H

#include "client_shifting_drawable.h"

#define ITEMS_IMG "../client_src/resources/items/items.png"


class DrawableValuable: public ShiftingDrawable {

public:
    DrawableValuable(SDL2pp::Renderer& renderer, SDL2pp::Point& cp, SDL2pp::Rect& textureRect,
                     SDL2pp::Rect& onMapRect, SoundManager& soundManager):
            ShiftingDrawable(renderer, cp, textureRect, onMapRect, soundManager) {}

    void setValuableFromSnapshot(const int valuable_type) {
        SDL2pp::Color color = {0, 128, 255, 1};  // Color en formato RGBA
        this->setTexture(ITEMS_IMG, color);
        switch (valuable_type) {
            case COIN:
                this->loadAnimations("../external/animations/valuables/coin.yml");
                break;
            case GEM:
                this->loadAnimations("../external/animations/valuables/gem.yml");
                break;
        }
    }
};

#endif  // CLIENT_VALUABLE_H
