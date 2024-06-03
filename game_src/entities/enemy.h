#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy: public Character {
private:
    // MODIFICACION DE POSICION
    int acc_y;

public:
    Enemy(int init_pos_x, int init_pos_y, PhysicalMap& map);
    void update();
};

#endif
