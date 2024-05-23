#ifndef CONSTANTS_GAME_H
#define CONSTANTS_GAME_H

enum /*COMMAND TYPE*/ {
    COMMAND_MOVE,
    COMMAND_MOVE_FASTER,
    COMMAND_JUMP,
    COMMAND_CHEAT,
    COMMAND_MATCH,
    COMMAND_SHOOT,
};

enum /*CHARACTERS*/ { RABBIT = 0, CRAB, LIZARD, RAT };

enum SupplyType : uint8_t {
    HEALTH_CARROT,
    AMMO_SUPPLY,
    GEM_SUPPLY,
    COIN_SUPPLY,
};

enum SupplyState : char {
    UNPICKED,
    PICKED,
};

enum /* CHEATS */ {
    ADD_HEALTH = 0,
};

// ----------------- Messurements -----------------

#define RABBIT_WIDTH 0.5
#define RABBIT_HEIGHT 0.5

#define MAP_WIDTH_DEFAULT 100   // modificar
#define MAP_HEIGHT_DEFAULT 100  // modificar

#endif
