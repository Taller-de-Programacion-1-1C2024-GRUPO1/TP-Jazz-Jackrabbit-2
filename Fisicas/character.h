#ifndef CHARACTER_H
#define CHARACTER_H

#include <queue>

#include "physical_objects.h"
class PhysicalMap;
// PLAYER CONSTANTS
enum ACTIONS {
    STAND,
    RUN,
    RUN_FAST,
    JUMPING,
    FALLING,
    JUMP_FORWARD,
    FALL_FORWARD,
    SHOOT,
    SPECIAL_ATTACK,
    DIE
};
enum DIRECTIONS { LEFT, RIGHT };

#define PLAYER_SIDE BLOCK_DIVISION * 2
#define PLAYER_SPEED 5
#define JUMPING_INITIAL_SPEED 10

// FISIC
#define GRAVITY 1

class Character: public PhysicalObject {

protected:
    int health;
    PhysicalMap& map;
    // MAP COLISION FLAGS
    bool on_floor;
    bool on_roof;
    bool on_left_wall;
    bool on_right_wall;

public:
    Character(int width, int height, int init_pos_x, int init_pos_y, PhysicalMap& map, int health):
            PhysicalObject(width, height, init_pos_x, init_pos_y),
            map(map),
            health(health),
            on_floor(false),
            on_roof(false),
            on_left_wall(false),
            on_right_wall(false) {}

    void receive_damage(int damage) { health -= damage; }

    void check_colision_with_bullet(int bullet_pos_x, int bullet_pos_y, int bullet_width,
                                    int bullet_height, int bullet_damage) {
        if (colision_checker(pos_x, pos_y, width, height, bullet_pos_x, bullet_pos_y, bullet_width,
                             bullet_height)) {
            receive_damage(bullet_damage);
        }
    }
    // COLISIONES CON MAPA
    void check_colision_with_map();
    void is_on_floor();
    void is_on_roof();
    void is_on_left_wall();
    void is_on_right_wall();
    void reset_map_colision_flags();
};

#define PLAYER_INITIAL_HEALTH 100

class Player: public Character {
private:
    int action;
    int direction;
    std::queue<int> events_queue;

    // MODIFICACION DE POSICION
    const int acc_y;

public:
    Player(int init_pos_x, int init_pos_y, PhysicalMap& map);
    void update();

    // EVENTS
    void jump();
    void run_right();
    void run_fast_right();
    void run_left();
    void run_fast_left();
    void shoot();
    void special_attack();

    // TESTING
    // RENDER
    void render(SDL_Renderer* renderer);
    void imprimir_posicion();

    // COLA
    void add_jump();
    void add_run_right();
    void add_run_fast_right();
    void add_run_left();
    void add_run_fast_left();
};

class Enemy: public Character {
private:
    // MODIFICACION DE POSICION
    int acc_y;

public:
    Enemy(int init_pos_x, int init_pos_y, PhysicalMap& map);
    // RENDER
    void render(SDL_Renderer* renderer);
};

#endif
