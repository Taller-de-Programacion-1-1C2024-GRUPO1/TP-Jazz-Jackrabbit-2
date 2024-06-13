#ifndef CLIENT_DRAWABLE_ENEMY_H
#define CLIENT_DRAWABLE_ENEMY_H

#include "client_shifting_drawable.h"

class DrawableEnemy: public ShiftingDrawable {
public:
    DrawableEnemy(SDL2pp::Renderer& renderer, SDL2pp::Point& cp, SDL2pp::Rect& textureRect,
                  SDL2pp::Rect& onMapRect, SoundManager& soundManager):
            ShiftingDrawable(renderer, cp, textureRect, onMapRect, soundManager) {}

    void setEnemyFromSnapshot(const int enemy_type) {
        SDL2pp::Color color = {0, 128, 255, 1};  // Color en formato RGBA
        switch (enemy_type) {
            case CRAB:
                this->setTexture(ENEMIES_PNG, color);
                this->loadAnimations(CRAB_ANIMATIONS);
                break;
            case LIZARD:
                this->setTexture(ENEMIES_PNG, color);
                this->loadAnimations(LIZARD_ANIMATIONS);
                break;
            case TURTLE:
                this->setTexture(TURTLE_PNG, color);
                this->loadAnimations(TURTLE_ANIMATIONS);
                break;
        }
    }
};

#endif  // CLIENT_DRAWABLE_ENEMY_H
