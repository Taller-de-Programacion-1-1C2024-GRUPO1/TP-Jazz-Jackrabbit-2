#ifndef HEARTSBANNER_H
#define HEARTSBANNER_H

#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "client_constants.h"

class HeartsBanner {
private:
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture texture;
    SDL2pp::Rect heartRect;
    int livesCounter;

public:
    explicit HeartsBanner(SDL2pp::Renderer& renderer);
    void setCurrentLives(int livesCount);
    void render();
};

#endif  // HEARTSBANNER_H
