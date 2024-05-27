#include "client_animation.h"

Animation::Animation(int f, int s, bool nc, const std::vector<SDL2pp::Rect>& rects) {
    frames = f;
    speed = s;
    needsCompletion = nc;
    frameRects = rects;
}
