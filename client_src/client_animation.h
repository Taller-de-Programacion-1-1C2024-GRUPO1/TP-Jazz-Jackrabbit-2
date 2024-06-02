#ifndef ANIMATION_H
#define ANIMATION_H
#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

struct Animation {
    std::string name;
    int frames;
    bool justOneLoop;
    std::vector<SDL2pp::Rect> frameRects;
    int currentFrame = 0;
    std::string sound;

    Animation() = default;

    Animation(const char* name, int f, bool oneLoop, const std::vector<SDL2pp::Rect>& rects,
              const char* sound):
            name(name),
            frames(f),
            justOneLoop(oneLoop),
            frameRects(rects),
            currentFrame(0),
            sound(sound) {}
};

#endif  // ANIMATION_H
