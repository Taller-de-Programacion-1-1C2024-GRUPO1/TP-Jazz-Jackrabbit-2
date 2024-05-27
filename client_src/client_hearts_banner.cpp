#include "client_hearts_banner.h"
#define HEART_IMG "../client_src/resources/items/items.png"

const int HEARTWIDTH = 18;
const int HEARTHEIGHT = 15;

HeartsBanner::HeartsBanner(SDL2pp::Renderer& renderer)
    : renderer(renderer), texture(renderer, SDL2pp::Surface(HEART_IMG)),
         heartRect(SDL2pp::Rect(444, 500, HEARTWIDTH, HEARTWIDTH)), heartCount(5) {
    SDL2pp::Surface surface(HEART_IMG);
    SDL_Color colorKey = {0, 128, 255, 1};
    SDL_SetColorKey(surface.Get(), SDL_TRUE,
                        SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b));
    this->texture = SDL2pp::Texture(renderer, surface);
}

void HeartsBanner::setHearts(int h) {
    heartCount = h;
}

void HeartsBanner::render() {
    for (int i = 0; i < heartCount; ++i) {
        SDL2pp::Rect currentRect(800 - (i+1) * 32, 0, 32, 32);
        renderer.Copy(texture, heartRect, currentRect);
    }
}