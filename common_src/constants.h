#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>

// FPS
#define UPDATE_RATE 60
#define DELTA_TIME 1000 / UPDATE_RATE

// ----------------- Generic Constants -----------------
// Queue codes DO NOT CHANGE
#define QUEUE_MAX_SIZE 10000

enum /*Senders*/ {
    READ_MAP = 0,
    READ_INFO,
    SEND_COMMAND,
    SEND_COMMAND_CHEAT,
    SEND_COMMAND_MATCH,
    SEND_COMMAND_JUMP,
    SEND_COMMAND_SHOOT,
    SEND_COMMAND_MOVE,
    SEND_COMMAND_MOVE_FASTER,
    ACK_MATCH_CREATED_SUCCEED,
    SEND_COMMAND_CHANGE_WEAPON,
    SEND_COMMAND_JUMP_PUNCH_ATTACK_JAZZ,
    SEND_COMMAND_SIDE_KICK_SPAZ,
    SEND_COMMAND_SHORT_RANGE_JUMP_KICK_LORI,
    SEND_COMMAND_SELECT_CHAMPION,
    SEND_GAME_INFO,
    ACK_JOINED_SUCCEED,
};

enum /*MATCH TYPE*/ {
    INVALID_MATCH_TYPE = -1,
    NEW_MATCH = 0,
    JOIN,
    REFRESH,
    PLAYER_CONNECTING,
};

enum /*INFO TYPE*/ {
    GAME_INFO = 1,
    SELECT_CHARACTER_INFO,
    GAME_MAP_INFO,
};

#define OK 0
#define ERROR_PROT 0xFF
#define ERROR -1
#define OK_MAP_CREATOR -2
#define INVALID_QT_RESPONSE -2

#define WAITING 0
#define STARTED 1

#define PLAYING -1

#define DEFAULT_MAP_CARROTUS "default_carrotus"
#define DEFAULT_MAP_CASTLE "default_castle"

#endif
