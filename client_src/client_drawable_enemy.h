#ifndef CLIENT_DRAWABLE_ENEMY_H
#define CLIENT_DRAWABLE_ENEMY_H

#include "client_shifting_drawable.h"
#include "client_textures_provider.h"

class DrawableEnemy: public ShiftingDrawable {
public:
    DrawableEnemy(SDL2pp::Renderer& renderer, SDL2pp::Point& cp, SDL2pp::Rect& textureRect,
                  SDL2pp::Rect& onMapRect, SoundManager& soundManager):
            ShiftingDrawable(renderer, cp, textureRect, onMapRect, soundManager) {}

    void setEnemyFromSnapshot(const int enemy_type) {
        switch (enemy_type) {
            case CRAB:
                this->setTexture(TexturesProvider::getTexture("Enemies"));
                this->loadAnimations(CRAB_ANIMATIONS);
                break;
            case LIZARD:
                this->setTexture(TexturesProvider::getTexture("Enemies"));
                this->loadAnimations(LIZARD_ANIMATIONS);
                break;
            case TURTLE:
                this->setTexture(TexturesProvider::getTexture("Turtle"));
                this->loadAnimations(TURTLE_ANIMATIONS);
                break;
        }
    }
};

#endif  // CLIENT_DRAWABLE_ENEMY_H
