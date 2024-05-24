#ifndef OBJETOSFISICOS_H
#define OBJETOSFISICOS_H
#include "SDL2/SDL.h"

#include <iostream> //////////TESTING


#define BLOCK_DIVISION 32 //Lado de un bloque mapa

//FPS
#define UPDATE_RATE 60
#define DELTA_TIME 1000/UPDATE_RATE

//FISIC
#define GRAVITY 1

/*
NOTAS:
*/
/*
COLISIONES:
Bullet -> Player
Bullet -> Enemy
*/
class PhysicalObject{
protected:

    const int width;
    const int height;
    int pos_x;
    int pos_y;
    int spe_x;
    int spe_y;

public:
    PhysicalObject(int width, int height,int init_pos_x, int init_pos_y) : 
    width(width), height(height),pos_x(init_pos_x), pos_y(init_pos_y), spe_x(0), spe_y(0){};

    bool colision_checker(int pos_x_A, int pos_y_A, int width_A, int height_A, int pos_x_B, int pos_y_B, int width_B, int height_B){
        return pos_x_A < pos_x_B + width_B && pos_x_A + width_A > pos_x_B &&
        pos_y_A < pos_y_B + height_B && pos_y_A + height_A > pos_y_B;
    };

    virtual ~PhysicalObject(){};
};


#endif
