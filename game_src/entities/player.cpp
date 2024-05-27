#include "player.h"

Player::Player(int init_pos_x, int init_pos_y, PhysicalMap& map):
        Character(PLAYER_SIDE, PLAYER_SIDE, init_pos_x, init_pos_y, map, PLAYER_INITIAL_HEALTH),
        action(STAND),
        acc_y(GRAVITY),
        direction(LEFT_DIR) {}

void Player::update() {
    check_colision_with_map();

    if (!on_floor && spe_y < MAX_FALLING_SPEED) {
        spe_y += acc_y;
    } else {
        spe_y = 0;
    }

    while (!events_queue.empty()) {
        int event = events_queue.front();
        events_queue.pop();
        printf("Event: %d\n", event);
        switch (event) {
            case EVENT_JUMP:
                jump();
                break;
            case EVENT_RUN_RIGHT:
                run_right();
                break;
            case EVENT_RUN_FAST_RIGHT:
                run_fast_right();
                break;
            case EVENT_RUN_LEFT:
                run_left();
                break;
            case EVENT_RUN_FAST_LEFT:
                run_fast_left();
                break;
        }
    }

    update_state();

    printf(action == STAND          ? "STAND\n" :
           action == RUN            ? "RUN\n" :
           action == RUN_FAST       ? "RUN_FAST\n" :
           action == JUMPING        ? "JUMPING\n" :
           action == FALLING        ? "FALLING\n" :
           action == JUMP_FORWARD   ? "JUMP_FORWARD\n" :
           action == FALL_FORWARD   ? "FALL_FORWARD\n" :
           action == SHOOT          ? "SHOOT\n" :
           action == SPECIAL_ATTACK ? "SPECIAL_ATTACK\n" :
                                      "DIE\n");
    // ACTUALIZA POSICIONES
    pos_x += spe_x;
    pos_y += spe_y;
    // NO HAY INERCIA
    spe_x = 0;
}

void Player::update_state() {
    // DIRECCION
    if (spe_x > 0) {
        direction = RIGHT_DIR;
    } else if (spe_x < 0) {
        direction = LEFT_DIR;
    }

    // CAMBIO DE ACCION
    if (!on_floor) {
        if (spe_y > 0) {
            if (spe_x != 0) {
                action = FALL_FORWARD;
            } else {
                action = FALLING;
            }
        } else {
            if (spe_x != 0) {
                action = JUMP_FORWARD;
            } else {
                action = JUMPING;
            }
        }
    } else if (spe_x == 0) {
        action = STAND;
    }

    // action = RUN_FAST;
}

void Player::render(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = pos_x;
    rect.y = pos_y;
    rect.w = width;
    rect.h = height;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Color rojo
    SDL_RenderFillRect(renderer, &rect);
}

void Player::imprimir_posicion() { printf("X: %d Y: %d\n", pos_x, pos_y); }

// EVENTS
// JUMP
void Player::jump() {
    if (on_floor) {
        spe_y = -JUMPING_INITIAL_SPEED;
    }
}
// RIGHT
void Player::run_right() {
    if (!on_right_wall) {
        spe_x = PLAYER_SPEED;
    }
}

// RIGHT SPRINT
void Player::run_fast_right() {
    if (on_floor && !on_right_wall) {
        spe_x = PLAYER_SPEED * 2;
    }
}

// LEFT_DIR
void Player::run_left() {
    if (!on_left_wall) {
        spe_x = -PLAYER_SPEED;
    }
}

// LEFT_DIR SPRINT
void Player::run_fast_left() {
    if (on_floor && !on_left_wall) {
        spe_x = -(PLAYER_SPEED * 2);
    }
}

// SHOOT
void Player::shoot() { action = SHOOT; }

// SPECIAL ATTACK
void Player::special_attack() { action = SPECIAL_ATTACK; }

// COLA
void Player::add_jump() { events_queue.push(EVENT_JUMP); }
void Player::add_run_right() { events_queue.push(EVENT_RUN_RIGHT); }
void Player::add_run_fast_right() { events_queue.push(EVENT_RUN_FAST_RIGHT); }
void Player::add_run_left() { events_queue.push(EVENT_RUN_LEFT); }
void Player::add_run_fast_left() { events_queue.push(EVENT_RUN_FAST_LEFT); }
