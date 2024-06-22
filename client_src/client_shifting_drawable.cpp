#include "client_shifting_drawable.h"

#include <fstream>

#include <yaml-cpp/yaml.h>

ShiftingDrawable::ShiftingDrawable(SDL2pp::Renderer& renderer, SDL2pp::Point& cp,
                                   SDL2pp::Rect& textureRect, SDL2pp::Rect& onMapRect,
                                   SoundManager& soundManager):
        Drawable(renderer, cp, textureRect, onMapRect),
        currentAnimation(new Animation()),
        angle(0),
        direction(0),
        iterationsBeetweenFrames(4),
        soundManager(soundManager) {}

// gets the animations from a yaml file
void ShiftingDrawable::loadAnimations(const std::string& path) {
    YAML::Node config = YAML::LoadFile(path);
    for (YAML::const_iterator it = config.begin(); it != config.end(); ++it) {
        Animation animation;
        animation.name = it->first.as<std::string>();
        animation.frames = it->second["frames"].as<int>();
        animation.justOneLoop = !it->second["loop"].as<bool>();
        animation.sound = it->second["sound"].as<std::string>();

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

void ShiftingDrawable::render() {
    renderer.Copy(*texture, textureRect, onMapRect, angle, SDL2pp::Point(0, 0),
                  direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void ShiftingDrawable::update() {
    Drawable::update();
    // std::cout << "Current frame: " << currentAnimation->currentFrame << std::endl;

    textureRect =
            currentAnimation->frameRects[currentAnimation->currentFrame % currentAnimation->frames];
    if (iterationsBeetweenFrames == 0) {
        iterationsBeetweenFrames = 4;
        if (currentAnimation->justOneLoop &&
            currentAnimation->currentFrame == currentAnimation->frames - 1) {
            return;
        } else if (currentAnimation->currentFrame == currentAnimation->frames - 1) {
            currentAnimation->currentFrame = 0;
        } else {
            currentAnimation->currentFrame++;
        }
    } else {
        iterationsBeetweenFrames--;
    }
}

void ShiftingDrawable::setAngle(int newAngle) { angle = newAngle; }
void ShiftingDrawable::setDirection(int dir) { direction = dir; }

void ShiftingDrawable::setAnimation(const char* name) {
    if (name == currentAnimation->name) {
        return;
    }
    currentAnimation->currentFrame = 0;
    currentAnimation = &animations[name];
    iterationsBeetweenFrames = 4;
    if (!currentAnimation->sound.empty()) {
        soundManager.playSoundEffect(currentAnimation->sound);
    }
}

void ShiftingDrawable::reajustFrame(int framesToAdvance) {
    if (framesToAdvance - iterationsBeetweenFrames < 0) {
        iterationsBeetweenFrames -= framesToAdvance;
    } else {
        int remainingFrames = framesToAdvance - iterationsBeetweenFrames;
        int animationFramesToAdvance = remainingFrames / 4;
        animationFramesToAdvance += 1;
        iterationsBeetweenFrames = (framesToAdvance + (4 - iterationsBeetweenFrames)) % 4;
        if (iterationsBeetweenFrames == 0) {
            iterationsBeetweenFrames = 4;
        }

        if (currentAnimation->justOneLoop) {
            if (currentAnimation->currentFrame + animationFramesToAdvance >=
                currentAnimation->frames) {
                currentAnimation->currentFrame = currentAnimation->frames - 1;
            }
        } else {
            if (currentAnimation->currentFrame + animationFramesToAdvance >=
                currentAnimation->frames) {
                currentAnimation->currentFrame =
                        (currentAnimation->currentFrame + animationFramesToAdvance) %
                        currentAnimation->frames;
            } else {
                currentAnimation->currentFrame += animationFramesToAdvance;
            }
        }
    }
}
