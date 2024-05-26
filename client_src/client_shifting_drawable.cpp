#include "client_shifting_drawable.h"

#include <fstream>

#include <yaml-cpp/yaml.h>

ShiftingDrawable::ShiftingDrawable(int x, int y, int w, int h, SDL2pp::Renderer& renderer,
                                   const std::string& path, const SDL_Color& colorKey):
        x(x), y(y), w(w), h(h), texture(renderer, SDL2pp::Surface(path)), angle(0) {
    SDL2pp::Surface surface(path);
    SDL_SetColorKey(surface.Get(), SDL_TRUE,
                    SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b));
    this->texture = SDL2pp::Texture(renderer, surface);
}

// gets the animations from a yaml file
void ShiftingDrawable::loadAnimations(const std::string& path) {
    YAML::Node config = YAML::LoadFile(path);
    for (YAML::const_iterator it = config.begin(); it != config.end(); ++it) {
        Animation animation;
        animation.frames = it->second["frames"].as<int>();
        animation.speed = it->second["speed"].as<int>();

        for (size_t i = 0; i < it->second["rects"].size(); i++) {
            SDL2pp::Rect rect;
            rect.x = it->second["rects"][i]["x"].as<int>();
            rect.y = it->second["rects"][i]["y"].as<int>();
            rect.w = it->second["rects"][i]["w"].as<int>();
            rect.h = it->second["rects"][i]["h"].as<int>();
            animation.frameRects.push_back(rect);
        }
        animations[it->first.as<std::string>()] = animation;
    }
    currentAnimationName = animations.begin()->first.c_str();
}

void ShiftingDrawable::render(SDL2pp::Renderer& renderer) {
    destRect = SDL2pp::Rect(x, y, w, h);
    renderer.Copy(texture, srcRect, destRect, angle, SDL2pp::Point(0, 0),
                  direction == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void ShiftingDrawable::update() {
    Animation* currentAnimation = &animations[currentAnimationName];
    int frame =
            static_cast<int>((SDL_GetTicks() / currentAnimation->speed) % currentAnimation->frames);
    srcRect = currentAnimation->frameRects[frame];
}

void ShiftingDrawable::setPosition(int newx, int newy) {
    x = newx;
    y = newy;
}

void ShiftingDrawable::setAngle(int newAngle) { angle = newAngle; }

void ShiftingDrawable::setDirection(int dir) { direction = dir; }

void ShiftingDrawable::setAnimation(const char* name) { currentAnimationName = name; }
