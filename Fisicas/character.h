#ifndef CHARACTER_H
#define CHARACTER_H

#include "physical_objects.h"
class PhysicalMap;

// FISIC
#define GRAVITY 1

class Character: public PhysicalObject {

protected:
    int health;
    PhysicalMap& map;
    // MAP COLISION FLAGS
    bool on_floor;
    bool on_roof;
    bool on_left_wall;
    bool on_right_wall;

public:
    Character(int width, int height, int init_pos_x, int init_pos_y, PhysicalMap& map, int health):
            PhysicalObject(width, height, init_pos_x, init_pos_y),
            map(map),
            health(health),
            on_floor(false),
            on_roof(false),
            on_left_wall(false),
            on_right_wall(false) {}

    void receive_damage(int damage) { health -= damage; }

    void check_colision_with_bullet(int bullet_pos_x, int bullet_pos_y, int bullet_width,
                                    int bullet_height, int bullet_damage) {
        if (colision_checker(pos_x, pos_y, width, height, bullet_pos_x, bullet_pos_y, bullet_width,
                             bullet_height)) {
            receive_damage(bullet_damage);
        }
    }
    // COLISIONES CON MAPA
    void check_colision_with_map();
    void is_on_floor();
    void is_on_roof();
    void is_on_left_wall();
    void is_on_right_wall();
    void reset_map_colision_flags();
};



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