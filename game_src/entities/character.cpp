#include "character.h"

Character::Character(int width, int height, int init_pos_x, int init_pos_y, PhysicalMap& map,
                     int health):
        PhysicalObject(width, height, init_pos_x, init_pos_y),
        map(map),
        health(health),
        on_floor(false),
        on_roof(false),
        on_left_wall(false),
        on_right_wall(false) {}

// COLISIONES CON MAPA
void Character::check_colision_with_map() {
    reset_map_colision_flags();
    map.check_colision_with_map(pos_x, pos_y, width, height, this);
}

void Character::is_on_floor() { on_floor = true; }

void Character::is_on_roof() { on_roof = true; }

void Character::is_on_left_wall() { on_left_wall = true; }

void Character::is_on_right_wall() { on_right_wall = true; }

void Character::reset_map_colision_flags() {
    on_floor = false;
    on_roof = false;
    on_left_wall = false;
    on_right_wall = false;
}
