#ifndef CLIENT_SHIFTING_DRAWABLE_H
#define CLIENT_SHIFTING_DRAWABLE_H

#include "../client_src/client_animation.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>

// Every entity that moves will be an instance of this class
class ShiftingDrawable {
private:
    int x, y, w, h;
    SDL2pp::Texture texture;
    std::map<std::string, Animation> animations; // Change this line
    const char* currentAnimationName;
    SDL2pp::Rect srcRect;
    SDL2pp::Rect destRect;
public:
    ShiftingDrawable() = delete;
    ShiftingDrawable(int x, int y, int w, int h, SDL2pp::Renderer& renderer, const std::string& path, const SDL_Color& colorKey);

    void loadAnimations(const std::string& path);
    void render(SDL2pp::Renderer& renderer);
    void update();
    void setPosition(int x, int y);
    void setAnimation(const char* name);

    //~ShiftingDrawable();
};

#endif //CLIENT_SHIFTING_DRAWABLE_H
