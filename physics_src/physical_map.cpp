#include "physical_map.h"

PhysicalMap::PhysicalMap(int map_width, int map_height,
                         const std::vector<std::vector<int>>& matrix):
        map_width(map_width), map_height(map_height), map(matrix) {}

void PhysicalMap::check_colision_with_map(int pos_x, int pos_y, int width, int height,
                                          Bullet* bullet) {
    int x0 = trunc((pos_x) / BLOCK_DIVISION);
    int y0 = trunc((pos_y) / BLOCK_DIVISION);
    int x2 = trunc((pos_x + width) / BLOCK_DIVISION);
    int y2 = trunc((pos_y + height) / BLOCK_DIVISION);
    if (y2 >= (map_height - 1) || (y0 <= 0) || (x0 <= 0) || x2 >= (map_width - 1) ||
        map[x0][y0] != NULL_OBJ || map[x2][y2] != NULL_OBJ || map[x0][y2] != NULL_OBJ ||
        map[x2][y0] != NULL_OBJ) {
        bullet->on_colision_with_map();
    }
}

bool PhysicalMap::can_jump(int pos_x, int pos_y, int width, int height) {
    int x0 = trunc((pos_x) / BLOCK_DIVISION);
    int x1 = trunc((pos_x + (width / 2)) / BLOCK_DIVISION);
    int x2 = trunc((pos_x + width) / BLOCK_DIVISION);
    int y2 = trunc((pos_y + height + 1) / BLOCK_DIVISION);
    return (((map[x0][y2]) + (map[x1][y2]) + (map[x2][y2])) > COLLIDER_OBJ) ||
           ((map[x0][y2]) == DIAG_LEFT_OBJ) || ((map[x2][y2]) == DIAG_RIGHT_OBJ);
}

void PhysicalMap::check_colision_with_map(int pos_x, int pos_y, int width, int height,
                                          Character* character) {
    int x0 = trunc((pos_x) / BLOCK_DIVISION);
    int y0 = trunc((pos_y) / BLOCK_DIVISION);
    int x1 = trunc((pos_x + (width / 2)) / BLOCK_DIVISION);
    int y1 = trunc((pos_y + (height / 2)) / BLOCK_DIVISION);
    int x2 = trunc((pos_x + width) / BLOCK_DIVISION);
    int y2 = trunc((pos_y + height) / BLOCK_DIVISION);

    if (y2 >= (map_height - 1) || ((map[x0][y2]) + (map[x1][y2]) + (map[x2][y2])) > COLLIDER_OBJ) {
        // std::cout << "on floor" << std::endl;
        character->is_on_floor();
    }
    if ((y0 <= 0) || ((map[x0][y0]) + (map[x1][y0]) + (map[x2][y0])) > COLLIDER_OBJ) {
        // std::cout << "on roof" << std::endl;
        character->is_on_roof();
    }
    if ((x0 <= 0) || ((map[x0][y0]) + (map[x0][y1]) + (map[x0][y2])) > COLLIDER_OBJ) {
        // std::cout << "on left wall" << std::endl;
        if ((map[x0][y1]) != DIAG_LEFT_OBJ) {
            character->is_on_left_wall();
        }
    }

    if (x2 >= (map_width - 1) || ((map[x2][y0]) + (map[x2][y1]) + (map[x2][y2])) > COLLIDER_OBJ) {
        // std::cout << "on right wall" << std::endl;
        if ((map[x2][y1]) != DIAG_RIGHT_OBJ) {
            character->is_on_right_wall();
        }
    }

    if ((map[x0][y2]) == DIAG_LEFT_OBJ) {
        if ((pos_x % BLOCK_DIVISION) <= pos_y % BLOCK_DIVISION) {
            character->is_on_left_slope();
        }
    } else if ((map[x2][y2]) == DIAG_RIGHT_OBJ) {
        if (pos_y % BLOCK_DIVISION >= (BLOCK_DIVISION - (pos_x % BLOCK_DIVISION))) {
            character->is_on_right_slope();
        }
    }

    /*
    SI SE QUIERE HACER QUE LAS DIAGOLES SEAN COLISIONABLES SI SE ENTRA POR EL LADO

    if (map[x2][y2] == DIAG_LEFT_OBJ || map[x2][y1] == DIAG_LEFT_OBJ) {
        character->is_on_right_wall();
    } else if (map[x0][y2] == DIAG_RIGHT_OBJ || map[x0][y1] == DIAG_RIGHT_OBJ) {
        character->is_on_left_wall();
    }
    */
}
