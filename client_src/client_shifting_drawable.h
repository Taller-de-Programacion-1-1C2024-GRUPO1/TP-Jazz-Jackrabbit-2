#ifndef CLIENT_SHIFTING_DRAWABLE_H
#define CLIENT_SHIFTING_DRAWABLE_H

#include <map>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "../client_src/client_animation.h"
#include "../client_src/client_drawable.h"
#include "../client_src/client_sound_manager.h"

// Every entity that moves will be an instance of this class
class ShiftingDrawable: public Drawable {
private:
    std::map<std::string, Animation> animations;
    Animation* currentAnimation;
    double angle;
    int direction;
    SoundManager& soundManager;
    int iterationsBeetweenFrames;

public:
    ShiftingDrawable(SDL2pp::Renderer& renderer, const std::string& path, const SDL_Color& colorKey,
                     SDL2pp::Point& cp, SDL2pp::Rect& textureRect, SDL2pp::Rect& onMapRect,
                     SoundManager& soundManager);

    void loadAnimations(const std::string& path);
    void render();
    void update();
    void setAngle(int angle);
    void setDirection(int dir);
    void setAnimation(const char* name);
    void reajustFrame(int framesToAdvance);

    //~ShiftingDrawable();
};

#endif  // CLIENT_SHIFTING_DRAWABLE_H
