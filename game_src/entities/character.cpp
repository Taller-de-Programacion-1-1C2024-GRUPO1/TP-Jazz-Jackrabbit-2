#include "character.h"

#include "../../physics_src/physical_map.h"

// COLISIONES CON MAPA
void Character::check_colision_with_map() {
    reset_map_colision_flags();
    physical_map.check_colision_with_map(pos_x, pos_y, width, height, this);
}

void Character::is_on_floor() { on_floor = true; }

void Character::is_on_roof() { on_roof = true; }

void Character::is_on_left_wall() { on_left_wall = true; }

void Character::is_on_right_wall() { on_right_wall = true; }

void Character::is_on_left_slope() { on_left_slope = true; }
void Character::is_on_right_slope() { on_right_slope = true; }
void Character::update_position() {
    // GRAVITY
    if (!on_floor && spe_y < MAX_FALLING_SPEED) {
        spe_y += acc_y;
    }
    // ACTUALIZA POSICIONES
    pos_x += spe_x;
    pos_y += spe_y;

    // REPOSITION
    check_colision_with_map();
    if (on_floor) {
        if (!on_left_slope && !on_right_slope) {
            pos_y = pos_y - ((pos_y % BLOCK_DIVISION) + 1);
        }
        spe_y = 0;
    }
    if (on_roof) {
        pos_y = pos_y + (BLOCK_DIVISION - (pos_y % BLOCK_DIVISION));
        spe_y = 0;
    }
    if (on_left_wall) {
        pos_x = pos_x + (BLOCK_DIVISION - (pos_x % BLOCK_DIVISION));
    }
    if (on_right_wall) {
        pos_x = pos_x - (pos_x % BLOCK_DIVISION);
    }

    check_colision_with_map();
    if (on_right_slope) {
        pos_y += BLOCK_DIVISION - (pos_x % BLOCK_DIVISION) - 1 - (pos_y % BLOCK_DIVISION);
        spe_y = 0;
    } else if (on_left_slope) {
        pos_y += (pos_x % BLOCK_DIVISION) - 1 - (pos_y % BLOCK_DIVISION);
        spe_y = 0;
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
