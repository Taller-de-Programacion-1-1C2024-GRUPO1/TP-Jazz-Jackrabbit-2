#ifndef CLIENT_RABBIT_H
#define CLIENT_RABBIT_H

#include "client_constants.h"
#include "client_shifting_drawable.h"
#include "client_textures_provider.h"

class DrawableRabbit: public ShiftingDrawable {

public:
    DrawableRabbit(SDL2pp::Renderer& renderer, SDL2pp::Point& cp, SDL2pp::Rect& textureRect,
                   SDL2pp::Rect& onMapRect, SoundManager& soundManager):
            ShiftingDrawable(renderer, cp, textureRect, onMapRect, soundManager) {}

    void setCharacterFromSnapshot(const int champion_type) {
        switch (champion_type) {
            case Jazz:
                this->setTexture(TexturesProvider::getTexture("Jazz"));
                this->loadAnimations(JAZZ_ANIMATIONS);
                break;
            case Spaz:
                this->setTexture(TexturesProvider::getTexture("Spaz"));
                this->loadAnimations(SPAZ_ANIMATIONS);
                break;
            case Lori:
                this->setTexture(TexturesProvider::getTexture("Lori"));
                this->loadAnimations(LORI_ANIMATIONS);
                break;
        }
    }

    void setAnimationFromSnapshot(const RabbitSnapshot& snapshot) {
        switch (snapshot.state) {
            case SPECIAL_ATTACK_LORI:
                this->setAnimation("Special-Attack");
                break;
            case SPECIAL_ATTACK_SPAZ:
                this->setAnimation("Special-Attack");
                break;
            case SPECIAL_ATTACK_JAZZ:
                this->setAnimation("Special-Attack");
                break;
            case ALIVE:
                switch (snapshot.action) {
                    case STAND:
                        this->setAnimation("Stand");
                        break;
                    case RUN_FAST:
                        this->setAnimation("Dash");
                        break;
                    case RUN:
                        this->setAnimation("Run");
                        break;
                    case FALLING:
                        this->setAnimation("Fall");
                        break;
                    case FALL_FORWARD:
                        this->setAnimation("Fall-Forward");
                        break;
                    case JUMPING:
                        this->setAnimation("Jump");
                        break;
                    case JUMP_FORWARD:
                        this->setAnimation("Jump-Forward");
                        break;
                    case SHOOT:
                        this->setAnimation("Shoot");
                        break;
                    default:
                        this->setAnimation("Stand");
                        break;
                }
                break;
            case RECIEVED_DAMAGE:
                this->setAnimation("Hurt");
                break;
            case INTOXICATED:
                switch (snapshot.action) {
                    case STAND:
                        this->setAnimation("Intoxicated-Stand");
                        break;
                    case RUN:
                        this->setAnimation("Intoxicated-Run");
                        break;
                    default:
                        this->setAnimation("Intoxicated-Stand");
                        break;
                }
                break;
            case DEAD:
                this->setAnimation("Die");
                break;
            default:
                std::cerr << "Unknown state" << std::endl;
                this->setAnimation("Stand");
                break;
        }
    }
};

#endif  // CLIENT_RABBIT_H
