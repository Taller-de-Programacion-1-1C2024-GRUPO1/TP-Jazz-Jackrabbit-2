#ifndef CLIENT_SHIFTING_DRAWABLE_H
#define CLIENT_SHIFTING_DRAWABLE_H

#include <map>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "../client_src/client_animation.h"
#include "../client_src/client_drawable.h"

// Every entity that moves will be an instance of this class
class ShiftingDrawable : public Drawable {
private:
    std::map<std::string, Animation> animations;  // Change this line
    const char* currentAnimationName;
    double angle;
    int direction;
    SDL2pp::Mixer& mixer;
public:
    ShiftingDrawable(SDL2pp::Renderer& renderer,
                    const std::string& path, const SDL_Color& colorKey,
                    SDL2pp::Point& cp, SDL2pp::Rect& textureRect, SDL2pp::Rect& onMapRect,
                    SDL2pp::Mixer& mixer);

    void loadAnimations(const std::string& path);
    void render(SDL2pp::Renderer& renderer);
    void update();
    void setAngle(int angle);
    void setDirection(int dir);
    void setAnimation(const char* name);

    //~ShiftingDrawable();
};

#endif  // CLIENT_SHIFTING_DRAWABLE_H
