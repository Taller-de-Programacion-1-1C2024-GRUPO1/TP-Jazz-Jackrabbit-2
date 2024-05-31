#ifndef HEARTSBANNER_H
#define HEARTSBANNER_H

#include <vector>

#include <SDL2pp/SDL2pp.hh>

class HeartsBanner {
private:
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture texture;
    SDL2pp::Rect heartRect;
    int heartCount;

public:
    explicit HeartsBanner(SDL2pp::Renderer& renderer);
    void setHearts(int heartCount);
    void render();
};

#endif  // HEARTSBANNER_H
