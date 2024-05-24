#ifndef PHYSICAL_MAP_H
#define PHYSICAL_MAP_H

#include <math.h> 
#define MAP_HEIGHT 10 //64
#define MAP_WIDTH 10 //128

#define BLOCK_DIVISION 32 //Lado de un bloque mapa

class Character;
/*
0 = Vacio
1 = Colisionable
2 = Diagonal
*/

class PhysicalMap {
private:
    int phisicaMap [MAP_WIDTH][MAP_HEIGHT];
    void position_on_map(int &pos_x, int &pos_y);

public:
    void load_map(int* map);
    void check_colision_with_map(int pos_x, int pos_y, int width, int height, Character* character);
};

#endif
