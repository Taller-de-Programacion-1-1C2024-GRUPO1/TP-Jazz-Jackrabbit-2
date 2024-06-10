#ifndef CHARACTER_H
#define CHARACTER_H

#include "../../physics_src/physical_objects.h"
#include "../constants_game.h"

class PhysicalMap;

class Character: public PhysicalObject {

protected:
    const int acc_y;
    int health;
    PhysicalMap& physical_map;
    // MAP COLISION FLAGS
    bool on_floor;
    bool on_roof;
    bool on_left_wall;
    bool on_right_wall;
    bool on_left_slope;
    bool on_right_slope;

public:
    Character(int width, int height, int init_pos_x, int init_pos_y, PhysicalMap& physical_map,
              int health):
            PhysicalObject(width, height, init_pos_x, init_pos_y),
            acc_y(GRAVITY),
            health(health),
            physical_map(physical_map),
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

    void update_position();
    // COLISONES CON ENTIDADES
    virtual void on_colision_with(PhysicalObject* object) override {}

    virtual void on_colision_with_enemy(Enemy* object) override {}
    virtual void on_colision_with_rabbit(Rabbit* object) override {}
    virtual void on_colision_with_item(Item* object) override {}
    virtual void on_colision_with_bullet(Bullet* object) override {}

    // COLISIONES CON MAPA
    void check_colision_with_map();
    void is_on_floor();
    void is_on_roof();
    void is_on_left_wall();
    void is_on_right_wall();
    void is_on_left_slope();
    void is_on_right_slope();
    void reset_map_colision_flags();
    virtual ~Character() {}
};

#endif
