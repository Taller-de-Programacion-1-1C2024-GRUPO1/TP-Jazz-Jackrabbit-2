#ifndef CLIENT_NUMBER_IMAGES_H
#define CLIENT_NUMBER_IMAGES_H

#include <vector>

#include "SDL2pp/SDL2pp.hh"

class NumberImages {
private:
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture numberTexture;
    std::vector<SDL2pp::Rect> numberRects;

public:
    explicit NumberImages(SDL2pp::Renderer& renderer);
    void renderNumber(int number, int offset);
    void loadNumbers();
};

#endif  // CLIENT_NUMBER_IMAGES_H
