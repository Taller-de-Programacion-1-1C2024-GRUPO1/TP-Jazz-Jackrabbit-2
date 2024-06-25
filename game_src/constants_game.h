#ifndef CONSTANTS_GAME_H
#define CONSTANTS_GAME_H

#include <cstdint>

#include "../server_src/config.h"

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

enum /*CHARACTERS*/ { RABBIT = 0, CRAB, LIZARD, TURTLE, NULL_ENEMY };

enum SupplyType : uint8_t {
    GEM,
    COIN,
    MACHINEGUN_AMMO,
    SNIPER_AMMO,
    HEALTH_CARROT,
    HOTDOG,
    HAMBURGER,
    ROTTEN_CHEESE,
    RAYGUN_AMMO
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

enum /* CHEATS */ { MAX_AMMO, MAX_HEALTH, RESPAWN, GODMODE };

enum RABBIT_STATES {
    ALIVE,
    DEAD,
    RECIEVED_DAMAGE,
    INTOXICATED,
    SPECIAL_ATTACK_JAZZ,
    SPECIAL_ATTACK_LORI,
    SPECIAL_ATTACK_SPAZ,
    GODMODE_STATE
};

#define WAITING 0
#define STARTED 1
#define PLAYING -1

#define NULL_ID -1

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

// ----------------- Messurements -----------------

//----------------- GAME CONSTANTS -----------------
#define GAME_DURATION_MINUTES ConfigSingleton::getInstance().getGameDurationMinutes()
#define BLOCK_DIVISION 32
#define MAP_WIDTH_DEFAULT 35
#define MAP_HEIGHT_DEFAULT 19
#define RABBIT_AMOUNT_DEFAULT 1

#define PLAYER_SIDE BLOCK_DIVISION * 2
#define RABBIT_COOLDOWN_TAKE_DAMAGE 3

#define RABBIT_WIDTH_DEFAULT PLAYER_SIDE
#define RABBIT_HEIGHT_DEFAULT PLAYER_SIDE


#define POINTS_KILLING_RABBIT ConfigSingleton::getInstance().getKillRabbitPoints()
#define JUMPING_INITIAL_SPEED ConfigSingleton::getInstance().getRabbitJumpSpeed()


//----------------- PHYSICS -----------------
#define GRAVITY 1
#define MAX_FALLING_SPEED 15
#define PLAYER_SPEED ConfigSingleton::getInstance().getRabbitSpeed()
#define RABBIT_REVIVAL_TIME ConfigSingleton::getInstance().getRabbitRevivalTime()
#define RABBIT_DEINTOXICATE_TIME ConfigSingleton::getInstance().getRabbitDeintoxicateTime()
#define JUMPING_INITIAL_SPEED ConfigSingleton::getInstance().getRabbitJumpSpeed()
#define SPECIAL_ATTACK_TIME JUMPING_INITIAL_SPEED / GRAVITY

//----------------- PLAYER CONSTANTS -----------------
#define PLAYER_INITIAL_HEALTH ConfigSingleton::getInstance().getPlayerStartingLife()
#define PLAYER_DAMAGE ConfigSingleton::getInstance().getPlayerDamage()
#define CARROT_HEALTH_AMOUNT ConfigSingleton::getInstance().getCantHealthCarrotLife()

//----------------- ENEMY CONSTANTS -----------------
#define ENEMY_WIDTH_DEFAULT BLOCK_DIVISION * 2   // modificar
#define ENEMY_HEIGHT_DEFAULT BLOCK_DIVISION * 2  // modificar

#define CRAB_BLOCKS_RANGE 8
#define LIZARD_BLOCKS_RANGE 8
#define TURTLE_BLOCKS_RANGE 4
#define CRAB_SPEED 4
#define LIZARD_SPEED 2
#define TURTLE_SPEED 1


#define CRAB_HEALTH ConfigSingleton::getInstance().getEnemyCrabLife()
#define LIZARD_HEALTH ConfigSingleton::getInstance().getEnemyLizardLife()
#define TURTLE_HEALTH ConfigSingleton::getInstance().getEnemyTurtleLife()

#define CRAB_DAMAGE ConfigSingleton::getInstance().getEnemyCrabDamage()
#define LIZARD_DAMAGE ConfigSingleton::getInstance().getEnemyLizardDamage()
#define TURTLE_DAMAGE ConfigSingleton::getInstance().getEnemyTurtleDamage()

#define CRAB_POINTS ConfigSingleton::getInstance().getEnemyCrabKillPoints()
#define LIZARD_POINTS ConfigSingleton::getInstance().getEnemyLizardKillPoints()
#define TURTLE_POINTS ConfigSingleton::getInstance().getEnemyTurtleKillPoints()

#define CRAB_REVIVE_SECONDS ConfigSingleton::getInstance().getEnemyCrabReviveSeconds()
#define LIZARD_REVIVE_SECONDS ConfigSingleton::getInstance().getEnemyLizardReviveSeconds()
#define TURTLE_REVIVE_SECONDS ConfigSingleton::getInstance().getEnemyTurtleReviveSeconds()

#define CRAB_DROP_AMOUNT ConfigSingleton::getInstance().getEnemyCrabDropAmount()
#define LIZARD_DROP_AMOUNT ConfigSingleton::getInstance().getEnemyLizardDropAmount()
#define TURTLE_DROP_AMOUNT ConfigSingleton::getInstance().getEnemyTurtleDropAmount()


//----------------- ENEMIES DROP PROBABILITIES (NO necesita que la sumatoria sea 100)
//-----------------

#define HOTDOG_DROP_PROBABILITY ConfigSingleton::getInstance().getHotdogDropProbability()
#define HAMBURGER_DROP_PROBABILITY ConfigSingleton::getInstance().getHamburgerDropProbability()
#define HEALTHCARROT_DROP_PROBABILITY \
    ConfigSingleton::getInstance().getHealthcarrotDropProbability()
#define COIN_DROP_PROBABILITY ConfigSingleton::getInstance().getCoinDropProbability()
#define GEM_DROP_PROBABILITY ConfigSingleton::getInstance().getGemDropProbability()
#define ROTTENCHEESE_DROP_PROBABILITY \
    ConfigSingleton::getInstance().getRottencheeseDropProbability()
#define MACHINEGUNAMMO_DROP_PROBABILITY \
    ConfigSingleton::getInstance().getMachinegunammoDropProbability()
#define SNIPERAMMO_DROP_PROBABILITY ConfigSingleton::getInstance().getSniperammoDropProbability()
#define RAYGUNAMMO_DROP_PROBABILITY ConfigSingleton::getInstance().getRaygunammoDropProbability()
#define NOTHING_DROP_PROBABILITY ConfigSingleton::getInstance().getNothingDropProbability()


#define HOTDOG_DROP_CONSTANT HOTDOG_DROP_PROBABILITY
#define HAMBURGER_DROP_CONSTANT HAMBURGER_DROP_PROBABILITY
#define HEALTHCARROT_DROP_CONSTANT HAMBURGER_DROP_CONSTANT + HEALTHCARROT_DROP_PROBABILITY
#define COIN_DROP_CONSTANT HEALTHCARROT_DROP_CONSTANT + COIN_DROP_PROBABILITY
#define GEM_DROP_CONSTANT COIN_DROP_CONSTANT + GEM_DROP_PROBABILITY
#define ROTTENCHEESE_DROP_CONSTANT GEM_DROP_CONSTANT + ROTTENCHEESE_DROP_PROBABILITY
#define MACHINEGUNAMMO_DROP_CONSTANT ROTTENCHEESE_DROP_CONSTANT + MACHINEGUNAMMO_DROP_PROBABILITY
#define SNIPERAMMO_DROP_CONSTANT MACHINEGUNAMMO_DROP_CONSTANT + SNIPERAMMO_DROP_PROBABILITY
#define RAYGUNAMMO_DROP_CONSTANT SNIPERAMMO_DROP_CONSTANT + RAYGUNAMMO_DROP_PROBABILITY
#define NOTHING_DROP_CONSTANT RAYGUNAMMO_DROP_CONSTANT + NOTHING_DROP_PROBABILITY
#define TOTAL_PROBABILITY NOTHING_DROP_CONSTANT


//----------------- POINTS CONSTANTS -----------------

#define COIN_POINTS ConfigSingleton::getInstance().getCoinPoints()
#define GEM_POINTS ConfigSingleton::getInstance().getGemPoints()
#define POINTS_KILLING_ENEMY ConfigSingleton::getInstance().getEnemyKillPoints()
#define HOTDOG_POINTS_AMOUNT ConfigSingleton::getInstance().getHotDogPoints()
#define HAMBURGER_POINTS_AMOUNT ConfigSingleton::getInstance().getHamburgerPoints()

//----------------- GUN CONSTANTS -----------------

#define CHANGE_WEAPON_COOLDOWN 10

enum GUN_TYPE { BASIC_GUN, FLAMETHROWER, ROCKETLAUNCHER, RAYGUN };

// BASIC GUN
#define BASIC_GUN_FIRE_COOLDOWN ConfigSingleton::getInstance().getBasicGunFireCooldown()
#define BASIC_GUN_MAX_AMMO 999
#define BASIC_GUN_DAMAGE ConfigSingleton::getInstance().getBasicGunDamage()
#define BASIC_GUN_RANGE ConfigSingleton::getInstance().getBasicGunRange()
#define BASIC_GUN_BULLET_SPEED ConfigSingleton::getInstance().getBasicGunBulletSpeed()

// FLAMETHROWER
#define FLAMETHROWER_FIRE_COOLDOWN ConfigSingleton::getInstance().getFlamethrowerFireCooldown()
#define FLAMETHROWER_MAX_AMMO ConfigSingleton::getInstance().getFlamethrowerMaxAmmo()
#define FLAMETHROWER_DAMAGE ConfigSingleton::getInstance().getFlamethrowerDamage()
#define FLAMETHROWER_RANGE ConfigSingleton::getInstance().getFlamethrowerRange()
#define FLAMETHROWER_BULLET_SPEED ConfigSingleton::getInstance().getFlamethrowerBulletSpeed()
#define FLAMETHROWER_AMMO_AMOUNT ConfigSingleton::getInstance().getFlamethrowerAmmoAmount()


// ROCKET LAUNCHER
#define ROCKETLAUNCHER_FIRE_COOLDOWN ConfigSingleton::getInstance().getRocketLauncherFireCooldown()
#define ROCKETLAUNCHER_MAX_AMMO ConfigSingleton::getInstance().getRocketLauncherMaxAmmo()
#define ROCKETLAUNCHER_DAMAGE ConfigSingleton::getInstance().getRocketLauncherDamage()
#define ROCKETLAUNCHER_RANGE ConfigSingleton::getInstance().getRocketLauncherRange()
#define ROCKETLAUNCHER_BULLET_SPEED ConfigSingleton::getInstance().getRocketLauncherBulletSpeed()
#define ROCKETLAUNCHER_AMMO_AMOUNT ConfigSingleton::getInstance().getRocketLauncherAmmoAmount()

// RAYGUN
#define RAYGUN_FIRE_COOLDOWN ConfigSingleton::getInstance().getRaygunFireCooldown()
#define RAYGUN_MAX_AMMO ConfigSingleton::getInstance().getRaygunMaxAmmo()
#define RAYGUN_DAMAGE ConfigSingleton::getInstance().getRaygunDamage()
#define RAYGUN_RANGE ConfigSingleton::getInstance().getRaygunRange()
#define RAYGUN_BULLET_SPEED ConfigSingleton::getInstance().getRaygunBulletSpeed()
#define RAYGUN_AMMO_AMOUNT ConfigSingleton::getInstance().getRaygunAmmoAmount()

#endif
