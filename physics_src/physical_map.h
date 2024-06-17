#ifndef PHYSICAL_MAP_H
#define PHYSICAL_MAP_H

#include <vector>

#include <math.h>

#include "../game_src/constants_game.h"
#include "../game_src/entities/bullet.h"
#include "../game_src/entities/character.h"
#include "../game_src/spawn_point.h"
#include "SDL2/SDL.h"

class Character;
/*
0 = Vacio
1 = Diagonal izquierda
2 = Diagonal derecha
4 = Colisionable
*/

class PhysicalMap {
public:
    int width = MAP_WIDTH_DEFAULT;
    int height = MAP_HEIGHT_DEFAULT;
    std::vector<std::vector<int>> map;
    PhysicalMap(int width, int height, const std::vector<std::vector<int>>& matrix);
    PhysicalMap() = default;
    void check_colision_with_map(int pos_x, int pos_y, int width, int height, Bullet* bullet);
    void check_colision_with_map(int pos_x, int pos_y, int width, int height, Character* character);
    bool can_jump(int pos_x, int pos_y, int width, int height);
};

#endif
