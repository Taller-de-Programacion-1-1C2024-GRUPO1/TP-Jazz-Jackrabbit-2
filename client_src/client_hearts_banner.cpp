#include "client_hearts_banner.h"

const int HEARTWIDTH = 18;
const int HEARTHEIGHT = 15;

HeartsBanner::HeartsBanner(SDL2pp::Renderer& renderer):
        renderer(renderer),
        texture(renderer, SDL2pp::Surface(ITEMS_PNG)),
        heartRect(SDL2pp::Rect(444, 500, HEARTWIDTH, HEARTWIDTH)),
        livesCounter(5) {
    SDL2pp::Surface surface(ITEMS_PNG);
    SDL_Color colorKey = {0, 128, 255, 1};
    SDL_SetColorKey(surface.Get(), SDL_TRUE,
                    SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b));
    this->texture = SDL2pp::Texture(renderer, surface);
}

void HeartsBanner::setCurrentLives(int lives) { livesCounter = lives; }

void HeartsBanner::render() {
    for (int i = 0; i < livesCounter; ++i) {
        SDL2pp::Rect currentRect(800 - (i + 1) * 32, 0, 32, 32);
        renderer.Copy(texture, heartRect, currentRect);
    }
}
