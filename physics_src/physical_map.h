#ifndef PHYSICAL_MAP_H
#define PHYSICAL_MAP_H

#include <math.h>

#include "../game_src/entities/character.h"
#include "SDL2/SDL.h"
#define MAP_HEIGHT 25  // 64
#define MAP_WIDTH 25   // 128

#define BLOCK_DIVISION 32  // Lado de un bloque mapa

class Character;
/*
0 = Vacio
1 = Diagonal izquierda
2 = Diagonal derecha
4 = Colisionable
*/

class PhysicalMap {
private:
    int map[MAP_WIDTH][MAP_HEIGHT];
    void load_map(const int* map);

public:
    void render(SDL_Renderer* renderer);
    explicit PhysicalMap(const int* map);
    void check_colision_with_map(int pos_x, int pos_y, int width, int height, Character* character);
};

#endif
