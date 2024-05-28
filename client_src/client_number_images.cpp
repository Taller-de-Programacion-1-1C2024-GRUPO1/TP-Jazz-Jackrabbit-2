#include "client_number_images.h"

#define FONT_IMG "../client_src/resources/fonts/Fonts.png"

NumberImages::NumberImages(SDL2pp::Renderer& renderer):
        x(0), y(0), renderer(renderer), numberTexture(renderer, SDL2pp::Surface(FONT_IMG)) {

    SDL2pp::Surface surface(FONT_IMG);
    SDL_Color colorKey = {0, 128, 255, 1};
    SDL_SetColorKey(surface.Get(), SDL_TRUE,
                    SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b));
    this->numberTexture = SDL2pp::Texture(renderer, surface);
    loadNumbers();
}

void NumberImages::loadNumbers() {
    numberRects.push_back(SDL2pp::Rect(548, 12, 25, 24));  // 0
    numberRects.push_back(SDL2pp::Rect(576, 10, 24, 24));  // 1
    numberRects.push_back(SDL2pp::Rect(612, 11, 30, 22));  // 2
    numberRects.push_back(SDL2pp::Rect(644, 10, 28, 25));  // 3
    numberRects.push_back(SDL2pp::Rect(678, 10, 29, 26));  // 4
    numberRects.push_back(SDL2pp::Rect(710, 10, 28, 22));  // 5
    numberRects.push_back(SDL2pp::Rect(744, 10, 24, 24));  // 6
    numberRects.push_back(SDL2pp::Rect(775, 10, 30, 24));  // 7
    numberRects.push_back(SDL2pp::Rect(805, 10, 28, 24));  // 8
    numberRects.push_back(SDL2pp::Rect(21, 42, 27, 28));   // 9
}

void NumberImages::setCorner(int mode) {
    switch (mode) {
        case 0:  // up left
            x = 0;
            y = 0;
            break;
        case 1:  // bottom right
            x = 800 - 32;
            y = 600 - 32;
            break;
    }
}

void NumberImages::renderNumber(int number, int offset) {
    renderer.Copy(numberTexture, numberRects[number], SDL2pp::Rect(x + offset, y, 32, 32));
}
