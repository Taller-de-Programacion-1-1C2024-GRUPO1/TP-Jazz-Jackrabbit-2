#include "client_shifting_drawable.h"

#include <fstream>

#include <yaml-cpp/yaml.h>

ShiftingDrawable::ShiftingDrawable(SDL2pp::Renderer& renderer, const std::string& path,
                                   const SDL_Color& colorKey, SDL2pp::Point& cp,
                                   SDL2pp::Rect& textureRect, SDL2pp::Rect& onMapRect,
                                   SDL2pp::Mixer& mixer):
        Drawable(renderer, path, cp, textureRect, onMapRect), angle(0), direction(0), mixer(mixer) {
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
        animation.name = it->first.as<std::string>();
        animation.frames = it->second["frames"].as<int>();
        animation.justOneLoop = !it->second["loop"].as<bool>();
        animation.soundPath = it->second["sound"].as<std::string>();

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
}

void ShiftingDrawable::render(SDL2pp::Renderer& renderer) {
    renderer.Copy(texture, textureRect, adjustPosition(), angle, SDL2pp::Point(0, 0),
                  direction == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void ShiftingDrawable::update() {
    Drawable::update();
    textureRect =
            currentAnimation.frameRects[currentAnimation.currentFrame % currentAnimation.frames];
    if (currentAnimation.justOneLoop &&
        currentAnimation.currentFrame == currentAnimation.frames - 1) {
        return;
    }
    currentAnimation.currentFrame++;
}

void ShiftingDrawable::setAngle(int newAngle) { angle = newAngle; }

void ShiftingDrawable::setDirection(int dir) { direction = dir; }

void ShiftingDrawable::setAnimation(const char* name) {
    if (name == currentAnimation.name) {
        return;
    }
    currentAnimation = animations[name];
    std::ifstream file(currentAnimation.soundPath.c_str());
    /*if (file.good()) {
        SDL2pp::Chunk soundEffect(animations[currentAnimationName].soundPath.c_str());
        mixer.PlayChannel(-1, soundEffect);
        SDL_Delay(500);
        mixer.HaltChannel(-1);
    }*/
}

void ShiftingDrawable::reajustFrame(int advancedFrame) {
    if (currentAnimation.justOneLoop &&
        currentAnimation.currentFrame == currentAnimation.frames - 1) {
        return;
    }
    currentAnimation.currentFrame = advancedFrame;
}
