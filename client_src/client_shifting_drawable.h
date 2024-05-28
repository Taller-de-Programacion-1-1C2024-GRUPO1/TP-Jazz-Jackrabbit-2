#ifndef CLIENT_SHIFTING_DRAWABLE_H
#define CLIENT_SHIFTING_DRAWABLE_H

#include <map>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "../client_src/client_animation.h"

// Every entity that moves will be an instance of this class
class ShiftingDrawable {
private:
    int x, y, w, h;
    SDL2pp::Texture texture;
    SDL2pp::Point cameraPosition;
    std::map<std::string, Animation> animations;  // Change this line
    const char* currentAnimationName;
    SDL2pp::Rect srcRect;
    SDL2pp::Rect destRect;
    double angle;
    int direction;
    SDL2pp::Mixer* mixer;

public:
    ShiftingDrawable() = delete;
    ShiftingDrawable(int x, int y, int w, int h, SDL2pp::Renderer& renderer,
                     const std::string& path, const SDL_Color& colorKey, SDL2pp::Mixer* mixer);

    void loadAnimations(const std::string& path);
    void render(SDL2pp::Renderer& renderer);
    void update();
    void setPosition(int x, int y);
    void setAngle(int angle);
    void setDirection(int dir);
    void setAnimation(const char* name);
    void setCameraPosition(const SDL2pp::Point& cameraPosition);
    void updateCameraPosition(const SDL2pp::Point& cameraPosition);


    //~ShiftingDrawable();
};

#endif  // CLIENT_SHIFTING_DRAWABLE_H
