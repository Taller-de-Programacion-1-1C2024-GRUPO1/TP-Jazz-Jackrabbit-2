#ifndef CLIENT_CLOCK
#define CLIENT_CLOCK

#include "client_number_images.h"
#include "SDL2pp/SDL2pp.hh"

class Clock {
private:
    int seconds = 0;
    int minutes = 0;
    NumberImages numberImages;

public:
    Clock(SDL2pp::Renderer& renderer): numberImages(renderer) {};

    void update(uint32_t current_time) {
        minutes = current_time / 60;
        seconds = current_time % 60;
    }

    void render() {
        std::string timeMin = minutes < 10 ? "0" + std::to_string(minutes) : std::to_string(minutes);
        std::string timeSec = seconds < 10 ? "0" + std::to_string(seconds) : std::to_string(seconds);
        int offset_x = 0;                             // Start position
        numberImages.setCorner(3);                     

        for (char c: timeMin) {
            int number = c - '0';  // Convert char to int
            numberImages.renderNumber(number, offset_x, 0, 32);
            offset_x += 24;  // Move position to the left for the next digit
        }
        numberImages.renderNumber(18, offset_x, 0, 32);  // Render :
        offset_x += 24;  // Move position to the left for the next digit
        for (char c: timeSec) {
            int number = c - '0';  // Convert char to int
            numberImages.renderNumber(number, offset_x, 0, 32);
            offset_x += 24;  // Move position to the left for the next digit
        }
    }
};

#endif //CLIENT_CLOCK