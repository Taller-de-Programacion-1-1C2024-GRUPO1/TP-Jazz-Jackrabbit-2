#ifndef CLIENT_NUMBER_IMAGES_H
#define CLIENT_NUMBER_IMAGES_H

#include <memory>
#include <vector>

#include "SDL2pp/SDL2pp.hh"

#include "client_constants.h"
#include "client_textures_provider.h"

class NumberImages {
private:
    int x, y;
    SDL2pp::Renderer& renderer;
    std::shared_ptr<SDL2pp::Texture> numbersTexture;
    std::vector<SDL2pp::Rect> numberRects;

public:
    explicit NumberImages(SDL2pp::Renderer& renderer);
    void renderNumber(int number, int offsetX, int offsetY, int size);
    void loadNumbers();
    void setCorner(int mode);
};

#endif  // CLIENT_NUMBER_IMAGES_H
