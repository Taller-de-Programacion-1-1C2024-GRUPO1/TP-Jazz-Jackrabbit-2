#ifndef CHARACTER_H
#define CHARACTER_H

#include "../../physics_src/physical_objects.h"
#define MAX_FALLING_SPEED 15
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
    bool on_left_slope;
    bool on_right_slope;

public:
    Character(int width, int height, int init_pos_x, int init_pos_y, PhysicalMap& map, int health):
            PhysicalObject(width, height, init_pos_x, init_pos_y),
            health(health),
            map(map),
            on_floor(false),
            on_roof(false),
            on_left_wall(false),
            on_right_wall(false),
            on_left_slope(false),
            on_right_slope(false) {}

    virtual void receive_damage(int damage) = 0;

    void check_colision_with_bullet(int bullet_pos_x, int bullet_pos_y, int bullet_width,
                                    int bullet_height, int bullet_damage) {
        if (colision_checker(pos_x, pos_y, width, height, bullet_pos_x, bullet_pos_y, bullet_width,
                             bullet_height)) {
            receive_damage(bullet_damage);
        }
    }

    //COLISONES CON ENTIDADES
    virtual void on_colision_with(PhysicalObject* object) = 0;

    virtual void on_colision_with_enemy(Enemy* object){};
    virtual void on_colision_with_rabbit(Rabbit* object){};
    virtual void on_colision_with_item(Item* object){};
    virtual void on_colision_with_bullet(Bullet* object){};

    // COLISIONES CON MAPA
    void check_colision_with_map();
    void is_on_floor();
    void is_on_roof();
    void is_on_left_wall();
    void is_on_right_wall();
    void is_on_left_slope();
    void is_on_right_slope();
    void reset_map_colision_flags();
    virtual ~Character(){};
};


#endif
