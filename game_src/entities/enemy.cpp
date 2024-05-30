#include "enemy.h"

#define ENEMY_INITIAL_HEALTH 100
Enemy::Enemy(int init_pos_x, int init_pos_y, PhysicalMap& map):
        Character(/*ANCHO ENEMIGO*/ BLOCK_DIVISION * 2, /*ALTO ENEMIGO*/ BLOCK_DIVISION, init_pos_x,
                  init_pos_y, map, /*VIDA ENEMIGO*/ ENEMY_INITIAL_HEALTH),
        acc_y(GRAVITY) {}


void Enemy::update() {
    check_colision_with_map();
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
            pos_y = pos_y - ((pos_y % BLOCK_DIVISION));
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
        if (spe_x > 0) {
            pos_y -= spe_x;
        }
    } else if (on_left_slope) {
        if (spe_x < 0) {
            pos_y += spe_x;
        }
    }

    // NO HAY INERCIA EN EJE X
    spe_x = 0;
}


// RENDER
void Enemy::render(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = pos_x;
    rect.y = pos_y;
    rect.w = width;
    rect.h = height;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Color verde
    SDL_RenderFillRect(renderer, &rect);
}
