#include "enemy.h"

#define ENEMY_INITIAL_HEALTH 100
Enemy::Enemy(int init_pos_x, int init_pos_y, PhysicalMap& map):
        Character(/*ANCHO ENEMIGO*/ BLOCK_DIVISION * 2, /*ALTO ENEMIGO*/ BLOCK_DIVISION, init_pos_x,
                  init_pos_y, map, /*VIDA ENEMIGO*/ ENEMY_INITIAL_HEALTH),
        acc_y(GRAVITY) {}


void Enemy::update() {
    check_colision_with_map();

    if (!on_floor) {
        spe_y += acc_y;
    } else {
        spe_y = 0;
    }

    // ACTUALIZA POSICIONES
    pos_x += spe_x;
    pos_y += spe_y;
    // NO HAY INERCIA
    spe_x = 0;
}


// RENDER
void Enemy::render(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = pos_x * 32;
    rect.y = pos_y * 32;
    rect.w = width;
    rect.h = height;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Color verde
    SDL_RenderFillRect(renderer, &rect);
}
