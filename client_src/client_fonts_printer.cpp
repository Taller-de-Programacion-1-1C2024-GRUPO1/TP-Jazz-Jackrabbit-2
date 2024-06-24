#include "client_fonts_printer.h"

FontPrinter::FontPrinter(SDL2pp::Renderer& renderer):
        x(0), y(0), renderer(renderer), fontsTexture(TexturesProvider::getTexture("Font")) {
    loadNumbers();
    loadLetters();
}

void FontPrinter::loadNumbers() {
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

void FontPrinter::loadLetters() {
    lettersRects['A'] = SDL2pp::Rect(286, 43, 25, 26);
    lettersRects['B'] = SDL2pp::Rect(318, 43, 25, 26);
    lettersRects['C'] = SDL2pp::Rect(351, 43, 25, 26);
    lettersRects['D'] = SDL2pp::Rect(384, 43, 25, 26);
    lettersRects['E'] = SDL2pp::Rect(418, 43, 25, 26);
    lettersRects['F'] = SDL2pp::Rect(451, 43, 25, 26);
    lettersRects['G'] = SDL2pp::Rect(484, 43, 25, 26);
    lettersRects['H'] = SDL2pp::Rect(517, 43, 25, 26);
    lettersRects['I'] = SDL2pp::Rect(550, 43, 25, 26);
    lettersRects['J'] = SDL2pp::Rect(583, 43, 25, 26);
    lettersRects['K'] = SDL2pp::Rect(616, 43, 25, 26);
    lettersRects['L'] = SDL2pp::Rect(648, 43, 22, 26);
    lettersRects['M'] = SDL2pp::Rect(680, 43, 25, 26);
    lettersRects['N'] = SDL2pp::Rect(713, 43, 25, 26);
    lettersRects['O'] = SDL2pp::Rect(747, 45, 25, 23);
    lettersRects['P'] = SDL2pp::Rect(780, 43, 23, 26);
    lettersRects['Q'] = SDL2pp::Rect(21, 79, 25, 26);
    lettersRects['R'] = SDL2pp::Rect(24, 79, 25, 24);
    lettersRects['S'] = SDL2pp::Rect(57, 79, 25, 24);
    lettersRects['T'] = SDL2pp::Rect(90, 79, 25, 24);
    lettersRects['U'] = SDL2pp::Rect(123, 80, 25, 24);
    lettersRects['V'] = SDL2pp::Rect(156, 79, 25, 24);
    lettersRects['W'] = SDL2pp::Rect(189, 79, 25, 24);
    lettersRects['X'] = SDL2pp::Rect(222, 79, 25, 24);
    lettersRects['Y'] = SDL2pp::Rect(256, 79, 23, 24);
    lettersRects['Z'] = SDL2pp::Rect(222, 79, 25, 24);
    lettersRects[':'] = SDL2pp::Rect(55, 46, 16, 23);
    lettersRects['-'] = SDL2pp::Rect(450, 12, 21, 20);
    lettersRects['x'] = SDL2pp::Rect(342, 303, 16, 21);
    lettersRects['*'] = SDL2pp::Rect(215, 288, 17, 20);
}

void FontPrinter::setCorner(int mode) {
    switch (mode) {
        case 0:  // up left
            x = 0;
            y = 0;
            break;
        case 1:  // bottom right
            x = SCREEN_WIDTH - BLOCK_DIVISION;
            y = SCREEN_HEIGHT - BLOCK_DIVISION;
            break;
        case 2:  // bottom left
            x = 0;
            y = SCREEN_HEIGHT - BLOCK_DIVISION;
            break;
        case 3:  // middle up
            x = SCREEN_WIDTH / 2 - (BLOCK_DIVISION / 2);
            y = 0;
            break;
    }
}

void FontPrinter::renderNumber(int number, int offset_x, int offset_y, int size) {
    renderer.Copy(*fontsTexture, numberRects[number],
                  SDL2pp::Rect(x + offset_x, y + offset_y, size, size));
}

void FontPrinter::renderLetter(char letter, int offset_x, int offset_y, int size) {
    renderer.Copy(*fontsTexture, lettersRects[letter],
                  SDL2pp::Rect(x + offset_x, y + offset_y, size, size));
}
