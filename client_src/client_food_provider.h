#ifndef CLIENT_FOOD_PROVIDER_H
#define CLIENT_FOOD_PROVIDER_H

#include <map>

#include <SDL2pp/SDL2pp.hh>

class FoodProvider {
private:
    static std::map<int, SDL2pp::Rect> foodMap;

public:
    static SDL2pp::Rect& getFood(int id) { 
        switch(id){
            case HEALTH_CARROT:
                return SDL2pp::Rect(310, 322, 32, 27);
            case HOTDOG:
                return SDL2pp::Rect(895, 890, 27, 27);
            case HAMBURGER:
                return SDL2pp::Rect(72, 889, 28, 31);
            case ROTTEN_CHEESE:
                return SDL2pp::Rect(153, 889, 30, 31);
        }
    }
};

std::map<int, SDL2pp::Rect> FoodProvider::foodMap;

#endif  // CLIENT_FOOD_PROVIDER_H
