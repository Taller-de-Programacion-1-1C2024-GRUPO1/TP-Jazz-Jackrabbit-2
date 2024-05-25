#include "client_animation.h"

Animation::Animation(int f, int s, const std::vector<SDL2pp::Rect>& rects){
    frames = f;
    speed = s;
    frameRects = rects;
}

