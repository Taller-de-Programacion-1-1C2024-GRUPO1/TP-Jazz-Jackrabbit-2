#ifndef ANIMATION_H
#define ANIMATION_H
#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

struct Animation {
    int frames;
    int speed;
    std::string soundPath;
    std::vector<SDL2pp::Rect> frameRects;

    Animation() = default;

    Animation(int f, int s, const char* sp, const std::vector<SDL2pp::Rect>& rects):
            frames(f), speed(s), soundPath(sp), frameRects(rects) {}
};

#endif  // ANIMATION_H
