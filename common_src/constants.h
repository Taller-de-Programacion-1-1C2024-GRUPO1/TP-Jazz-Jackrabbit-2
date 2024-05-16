#ifndef UTILS_H
#define UTILS_H

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

#endif
