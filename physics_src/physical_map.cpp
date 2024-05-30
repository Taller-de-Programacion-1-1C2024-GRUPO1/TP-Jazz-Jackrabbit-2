#include "physical_map.h"


PhysicalMap::PhysicalMap(const int* map) { load_map(map); }

void PhysicalMap::load_map(const int* map_array) {
    for (int j = 0; j < MAP_HEIGHT; j++) {
        for (int i = 0; i < MAP_WIDTH; i++) {
            map[i][j] = map_array[j * MAP_WIDTH + i];
        }
    }
}

void PhysicalMap::render(SDL_Renderer* renderer) {
    for (int j = 0; j < MAP_HEIGHT; j++) {
        for (int i = 0; i < MAP_WIDTH; i++) {
            if (map[i][j] == 1) {
                SDL_Rect blockRect = {i * BLOCK_DIVISION, j * BLOCK_DIVISION, BLOCK_DIVISION,
                                      BLOCK_DIVISION};
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                SDL_RenderFillRect(renderer, &blockRect);
            }
            if (map[i][j] == 2) {
                SDL_Rect blockRect = {i * BLOCK_DIVISION, j * BLOCK_DIVISION, BLOCK_DIVISION,
                                      BLOCK_DIVISION};
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderFillRect(renderer, &blockRect);
            }
            if (map[i][j] == 4) {
                SDL_Rect blockRect = {i * BLOCK_DIVISION, j * BLOCK_DIVISION, BLOCK_DIVISION,
                                      BLOCK_DIVISION};
                SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
                SDL_RenderFillRect(renderer, &blockRect);
            }
        }
    }
}

void PhysicalMap::check_colision_with_map(int pos_x, int pos_y, int width, int height,
                                          Character* character) {
    int x0 = trunc((pos_x) / BLOCK_DIVISION);
    int y0 = trunc((pos_y) / BLOCK_DIVISION);
    int x1 = trunc((pos_x + (width / 2)) / BLOCK_DIVISION);
    int y1 = trunc((pos_y + (height / 2)) / BLOCK_DIVISION);
    int x2 = trunc((pos_x + width) / BLOCK_DIVISION);
    int y2 = trunc((pos_y + height) / BLOCK_DIVISION);

    // printf("x0: %d, x1: %d, x2: %d, y0: %d, y1: %d, y2: %d\n", x0, x1, x2, y0, y1, y2);
    if (((map[x0][y2]) + (map[x1][y2]) + (map[x2][y2])) > 4) {
        // printf("on floor");
        character->is_on_floor();
    }
    if (((map[x0][y0]) + (map[x1][y0]) + (map[x2][y0])) > 4) {
        // printf("on roof");
        character->is_on_roof();
    }
    if (((map[x0][y0]) + (map[x0][y1]) + (map[x0][y2])) > 4) {
        // printf("on left wall");
        character->is_on_left_wall();
    }
    if (((map[x2][y0]) + (map[x2][y1]) + (map[x2][y2])) > 4) {
        // printf("on right wall");
        character->is_on_right_wall();
    }


    if ((map[x0][y2]) == 1 || (map[x0][y1]) == 1) {
        character->is_on_left_slope();
    } else if ((map[x2][y2]) == 2 || (map[x2][y1]) == 2) {
        character->is_on_right_slope();
    }

    if (map[x2][y2] == 1 || map[x2][y1] == 1) {
        character->is_on_right_wall();
    } else if (map[x0][y2] == 2 || map[x0][y1] == 2) {
        character->is_on_left_wall();
    }
}
