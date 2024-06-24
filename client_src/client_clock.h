#ifndef CLIENT_CLOCK
#define CLIENT_CLOCK

#include <string>

#include "SDL2pp/SDL2pp.hh"

#include "client_fonts_printer.h"

class Clock {
private:
    int seconds = 0;
    int minutes = 0;
    FontPrinter fontPrinter;

public:
    explicit Clock(SDL2pp::Renderer& renderer): fontPrinter(renderer) {}

    void update(uint32_t current_time) {
        minutes = current_time / 60;
        seconds = current_time % 60;
    }

    void render() {
        std::string timeMin =
                minutes < 10 ? "0" + std::to_string(minutes) : std::to_string(minutes);
        std::string timeSec =
                seconds < 10 ? "0" + std::to_string(seconds) : std::to_string(seconds);
        int offset_x = 0;  // Start position
        fontPrinter.setCorner(3);

        for (char c: timeMin) {
            int number = c - '0';  // Convert char to int
            fontPrinter.renderNumber(number, offset_x, 0, BLOCK_DIVISION);
            offset_x += 24;  // Move position to the left for the next digit
        }
        fontPrinter.renderLetter(':', offset_x, 0, BLOCK_DIVISION);
        offset_x += 24;  // Move position to the left for the next digit
        for (char c: timeSec) {
            int number = c - '0';  // Convert char to int
            fontPrinter.renderNumber(number, offset_x, 0, BLOCK_DIVISION);
            offset_x += 24;  // Move position to the left for the next digit
        }
    }
};

#endif  // CLIENT_CLOCK
