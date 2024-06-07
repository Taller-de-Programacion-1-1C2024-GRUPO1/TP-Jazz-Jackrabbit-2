#ifndef CLIENT_FOOD_PROVIDER_H
#define CLIENT_FOOD_PROVIDER_H

#include <map>

#include <SDL2pp/SDL2pp.hh>

class FoodProvider {
private:
    static std::map<int, SDL2pp::Rect> foodMap;

public:
    static void initialize() {
        foodMap[0] = SDL2pp::Rect(72, 889, 28, 31);   // hamburguesa
        foodMap[1] = SDL2pp::Rect(153, 889, 30, 31);  // queso
        foodMap[2] = SDL2pp::Rect(895, 890, 27, 27);  // pancho
    }
    static SDL2pp::Rect& getFood(int id) { return foodMap[id]; }
};

std::map<int, SDL2pp::Rect> FoodProvider::foodMap;

#endif  // CLIENT_FOOD_PROVIDER_H
