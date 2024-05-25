#include "character.h"

#include "physical_map.h"

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

#define ENEMY_INITIAL_HEALTH 100
Enemy::Enemy(int init_pos_x, int init_pos_y, PhysicalMap& map):
        Character(/*ANCHO ENEMIGO*/ BLOCK_DIVISION*2, /*ALTO ENEMIGO*/ BLOCK_DIVISION, init_pos_x,
                  init_pos_y, map, /*VIDA ENEMIGO*/ ENEMY_INITIAL_HEALTH),
        acc_y(GRAVITY) {}

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
