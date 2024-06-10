#ifndef CONSTANTS_GAME_H
#define CONSTANTS_GAME_H

#include <cstdint>

enum /*COMMAND TYPE*/ {
    COMMAND_MOVE,
    COMMAND_MOVE_FASTER,
    COMMAND_JUMP,
    COMMAND_CHEAT,
    COMMAND_MATCH,
    COMMAND_SELECT_CHAMPION,
    COMMAND_SHOOT,
    COMMAND_CHANGE_WEAPON,
    COMMAND_JUMP_PUNCH_ATTACK_JAZZ,
    COMMANDS_SIDE_KICK_SPAZ,
    COMMANDS_SHORT_RANGE_JUMP_KICK_LORI,
};

enum ChampionType : uint8_t {
    NULL_CHAMPION_TYPE = 0,
    Jazz,
    Spaz,
    Lori,
};

enum /*CHARACTERS*/ { RABBIT = 0, CRAB, LIZARD, TURTLE };

enum SupplyType : uint8_t {
    HEALTH_CARROT,
    AMMO,
    GEM,
    COIN,
};

enum DIRECTIONS { LEFT, RIGHT, UP, DOWN };

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

enum SupplyState : char {
    UNPICKED,
    PICKED,
};

enum /* CHEATS */ {
    ADD_HEALTH = 0,
};

enum GUN_TYPE { BASIC_GUN, MACHINE_GUN, SNIPER };


enum RABBIT_STATES { ALIVE, DEAD, RECIEVED_DAMAGE, INTOXICATED };

#define WAITING 0
#define STARTED 1
#define PLAYING -1

#define NULL_ID -1

// ----------------- Messurements -----------------

#define BLOCK_DIVISION 32

// PLAYER CONSTANTS
#define PLAYER_SIDE BLOCK_DIVISION * 2
#define RABBIT_COOLDOWN_TAKE_DAMAGE 3

#define RABBIT_WIDTH_DEFAULT PLAYER_SIDE   // modificar
#define RABBIT_HEIGHT_DEFAULT PLAYER_SIDE  // modificar

// ENEMY CONSTANTS
#define ENEMY_INITIAL_HEALTH 3                   // Config
#define ENEMY_WIDTH_DEFAULT BLOCK_DIVISION * 2   // modificar
#define ENEMY_HEIGHT_DEFAULT BLOCK_DIVISION * 2  // modificar

#define GRAVITY 1
#define MAX_FALLING_SPEED 15

#define RABBIT_AMOUNT_DEFAULT 1  // modificar

#define MAP_WIDTH_DEFAULT 35   // modificar
#define MAP_HEIGHT_DEFAULT 19  // modificar

enum /*MAP LAYERS*/ {
    BACKGROUND_LAYER = 0,
    DIAG_LEFT_LAYER,
    DIAG_RIGHT_LAYER,
    COLLIDER_LAYER,
    DECORATION_LAYER,
    SPAWN_POINTS_LAYER,
};

enum /*MAP OBJECTS*/ {
    NULL_OBJ = 0,
    DIAG_LEFT_OBJ,
    DIAG_RIGHT_OBJ,
    COLLIDER_OBJ = 4,
};

enum /*SPAWN POINTS*/ {
    RABBIT_SPAWN = 0,
    LIZARD_SPAWN,
    CRAB_SPAWN,
    TURTLE_SPAWN,
    COIN_SPAWN,
    GEM_SPAWN,
};

#define UNDEFINED -1

#endif
