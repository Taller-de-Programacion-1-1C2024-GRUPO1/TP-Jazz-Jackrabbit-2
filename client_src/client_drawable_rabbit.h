#ifndef CLIENT_RABBIT_H
#define CLIENT_RABBIT_H

#include "client_shifting_drawable.h"

#define JAZZ_IMG "../client_src/resources/characters/Jazz.png"
#define LORI_IMG "../client_src/resources/characters/Lori.png"
#define SPAZ_IMG "../client_src/resources/characters/Spaz.png"

class DrawableRabbit: public ShiftingDrawable {

public:
    DrawableRabbit(SDL2pp::Renderer& renderer, SDL2pp::Point& cp, SDL2pp::Rect& textureRect,
                   SDL2pp::Rect& onMapRect, SoundManager& soundManager):
            ShiftingDrawable(renderer, cp, textureRect, onMapRect, soundManager) {}

    void setCharacterFromSnapshot(const int champion_type) {
        SDL2pp::Color characterColor = {44, 102, 150, 255};  // Color en formato RGBA
        switch (champion_type) {
            case Jazz:
                this->setTexture(JAZZ_IMG, characterColor);
                this->loadAnimations("../external/animations/jazz.yml");
                break;
            case Spaz:
                this->setTexture(SPAZ_IMG, characterColor);
                this->loadAnimations("../external/animations/spaz.yml");
                break;
            case Lori:
                this->setTexture(LORI_IMG, characterColor);
                this->loadAnimations("../external/animations/lori.yml");
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
                std::cout << "Alive" << std::endl;
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
