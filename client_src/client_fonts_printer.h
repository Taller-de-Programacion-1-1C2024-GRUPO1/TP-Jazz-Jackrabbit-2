#ifndef CLIENT_FONT_PRINTER
#define CLIENT_FONT_PRINTER

#include <map>
#include <memory>
#include <vector>

#include "../game_src/constants_game.h"
#include "SDL2pp/SDL2pp.hh"

#include "client_constants.h"
#include "client_textures_provider.h"

class FontPrinter {
private:
    int x, y;
    SDL2pp::Renderer& renderer;
    std::shared_ptr<SDL2pp::Texture> fontsTexture;
    std::vector<SDL2pp::Rect> numberRects;
    std::map<char, SDL2pp::Rect> lettersRects;

public:
    explicit FontPrinter(SDL2pp::Renderer& renderer);
    void renderNumber(int number, int offsetX, int offsetY, int size);
    void renderLetter(char letter, int offsetX, int offsetY, int size);
    void loadNumbers();
    void loadLetters();
    void setCorner(int mode);
};

#endif  // CLIENT_FONT_PRINTER
