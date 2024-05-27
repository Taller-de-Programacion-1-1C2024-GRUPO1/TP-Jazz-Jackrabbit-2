#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>

#include <SDL2pp/SDL2pp.hh>

struct Animation {
    int frames;
    int speed;
    bool needsCompletion;
    std::vector<SDL2pp::Rect> frameRects;

    Animation() {}

    Animation(int f, int s, bool nc, const std::vector<SDL2pp::Rect>& rects);
};

#endif  // ANIMATION_H
