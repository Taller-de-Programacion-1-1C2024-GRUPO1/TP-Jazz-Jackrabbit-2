#include "character.h"

#include "../../physics_src/physical_map.h"

// COLISIONES CON MAPA
void Character::check_colision_with_map() {
    reset_map_colision_flags();
    map.check_colision_with_map(pos_x, pos_y, width, height, this);
}

void Character::is_on_floor() { on_floor = true; }

void Character::is_on_roof() { on_roof = true; }

void Character::is_on_left_wall() { on_left_wall = true; }

void Character::is_on_right_wall() { on_right_wall = true; }

void Character::is_on_left_slope() {
    on_left_slope = true;
    if (((pos_x % BLOCK_DIVISION)) <= pos_y % BLOCK_DIVISION) {
        on_floor = true;
    }
}
void Character::is_on_right_slope() {
    on_right_slope = true;
    if ((pos_x % BLOCK_DIVISION) + (BLOCK_DIVISION * 1.5) >= pos_y % BLOCK_DIVISION) {
        on_floor = true;
    }
}

void Character::reset_map_colision_flags() {
    on_floor = false;
    on_roof = false;
    on_left_wall = false;
    on_right_wall = false;
    on_left_slope = false;
    on_right_slope = false;
}
