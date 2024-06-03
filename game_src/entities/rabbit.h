#ifndef PLAYER_H
#define PLAYER_H

#include <queue>

#include "../../common_src/constants.h"
#include "../constants_game.h"

#include "character.h"

#define PLAYER_SIDE BLOCK_DIVISION * 2
#define PLAYER_INITIAL_HEALTH 100
#define PLAYER_SPEED 5
#define JUMPING_INITIAL_SPEED 20

// TESTING
enum EVENTS {
    EVENT_JUMP,
    EVENT_RUN_RIGHT,
    EVENT_RUN_FAST_RIGHT,
    EVENT_RUN_LEFT,
    EVENT_RUN_FAST_LEFT,
    EVENT_SHOOT,
    EVENT_SPECIAL_ATTACK
};

class Rabbit: public Character {
private:
    int action;
    int direction;
    std::queue<int> events_queue;

    // MODIFICACION DE POSICION
    const int acc_y;

public:
    Rabbit(int init_pos_x, int init_pos_y, PhysicalMap& map);
    void update();
    void update_state();
    void update_position();

    // EVENTS
    void handle_events();

    void jump();
    void run_right();
    void run_fast_right();
    void run_left();
    void run_fast_left();
    void shoot();
    void special_attack();

    // TESTING
    // RENDER
    void imprimir_posicion();

    // COLA
    void add_jump();
    void add_run_right();
    void add_run_fast_right();
    void add_run_left();
    void add_run_fast_left();
    void add_shoot();
};

#endif
