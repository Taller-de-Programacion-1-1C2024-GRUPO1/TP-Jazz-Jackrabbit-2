#ifndef OBJETOSFISICOS_H
#define OBJETOSFISICOS_H

#include <iostream>  //////////TESTING

#include "../common_src/constants.h"
#include "SDL2/SDL.h"

class Enemy;
class Rabbit;
class Item;
class Bullet;


/*
NOTAS:
*/
/*
COLISIONES:
Bullet -> Rabbit
Bullet -> Enemy
*/
class PhysicalObject {
protected:
    const int width;
    const int height;
    int pos_x;
    int pos_y;
    int spe_x;
    int spe_y;
    bool dead;

public:
    PhysicalObject(int width, int height, int init_pos_x, int init_pos_y):
            width(width),
            height(height),
            pos_x(init_pos_x),
            pos_y(init_pos_y),
            spe_x(0),
            spe_y(0),
            dead(false) {}

    bool colision_checker(int pos_x_A, int pos_y_A, int width_A, int height_A, int pos_x_B,
                          int pos_y_B, int width_B, int height_B) {
        return pos_x_A < pos_x_B + width_B && pos_x_A + width_A > pos_x_B &&
               pos_y_A < pos_y_B + height_B && pos_y_A + height_A > pos_y_B;
    }

    void check_colision_with(PhysicalObject* second_object) {
        second_object->check_colision_with(pos_x, pos_y, width, height, this);
    }

    void check_colision_with(int other_position_x, int other_position_y, int other_width,
                             int other_height, PhysicalObject* first_object) {
        if (colision_checker(pos_x, pos_y, width, height, other_position_x, other_position_y,
                             other_width, other_height)) {
            first_object->on_colision_with(this);
        }
    }

    virtual void on_colision_with(PhysicalObject* first_object) = 0;

    virtual void on_colision_with_enemy(Enemy* second_object) {}
    virtual void on_colision_with_rabbit(Rabbit* second_object) {}
    virtual void on_colision_with_item(Item* second_object) {}
    virtual void on_colision_with_bullet(Bullet* second_object) {}


    bool is_dead() { return dead; }

    void kill() { dead = true; }

    virtual ~PhysicalObject() {}
};


#endif
