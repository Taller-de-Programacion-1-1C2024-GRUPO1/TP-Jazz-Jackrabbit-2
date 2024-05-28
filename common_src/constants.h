#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>

#define LOOP_TIME 200
#define NUM_OF_ENEMIES 5

#define ATACK static_cast<const uint8_t>(3)
#define READ static_cast<const uint8_t>(0)
#define EXIT static_cast<const uint8_t>(1)
#define INVALID static_cast<const uint8_t>(-1)
#define EVENT_DEAD_8 static_cast<const uint8_t>(4)
#define EVENT_RESURRECT_8 static_cast<const uint8_t>(5)

#define EVENT_DEAD static_cast<const uint16_t>(4)
#define EVENT_RESURRECT static_cast<const uint16_t>(5)
#define MSG_INDICATOR static_cast<const uint16_t>(6)
#define NUM_OF_ITERATIONS_TO_RESURRECT 15

struct Message {
    // cppcheck-suppress unusedStructMember
    uint8_t msg_indicator;
    // cppcheck-suppress unusedStructMember
    uint16_t num_alive_enemies;
    // cppcheck-suppress unusedStructMember
    uint16_t num_dead_enemies;
    // cppcheck-suppress unusedStructMember
    uint8_t event_type;
};

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
    ACK_JOINED_SUCCEED,
};

enum /*Direction*/ {
    LEFT_DIR = 0,
    RIGHT_DIR,
    FORWARD_DIR,
    BACKWARD_DIR,
};

enum /*MATCH TYPE*/ {
    NEW_MATCH = 0,
    JOIN,
    REFRESH,
};

enum /*GAME TYPE*/ {
    GAME_MAP = 0,
    GAME_INFO,
};


#define WAITING 0
#define STARTED 1

#define PLAYING -1

#endif
