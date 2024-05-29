#ifndef CONSTANTS_GAME_H
#define CONSTANTS_GAME_H

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
    Jazz,
    Spaz,
    Lori,
};

enum /*CHARACTERS*/ { RABBIT = 0, CRAB, LIZARD, RAT };

enum SupplyType : uint8_t {
    HEALTH_CARROT,
    AMMO_SUPPLY,
    GEM_SUPPLY,
    COIN_SUPPLY,
};

enum actions {
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

// ----------------- Messurements -----------------

#define ENEMY_INITIAL_HEALTH 100  // Se puede modificar

#define RABBIT_WIDTH_DEFAULT 32   // modificar
#define RABBIT_HEIGHT_DEFAULT 32  // modificar

#define RABBIT_AMOUNT_DEFAULT 1  // modificar

#define MAP_WIDTH_DEFAULT 100   // modificar
#define MAP_HEIGHT_DEFAULT 100  // modificar

#endif
