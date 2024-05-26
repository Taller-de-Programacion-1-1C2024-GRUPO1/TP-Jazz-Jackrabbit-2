#ifndef ENEMY_H
#define ENEMY_H

#include "../../physics_src/physical_objects.h"
#include "../../physics_src/physical_map.h"

class Enemy: public Character {
private:
    // MODIFICACION DE POSICION
    int acc_y;

public:
    Enemy(int init_pos_x, int init_pos_y, PhysicalMap& map);
    // RENDER
    void render(SDL_Renderer* renderer);
};

#endif
