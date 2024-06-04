#ifndef CONSTANTS_SERVER_H
#define CONSTANTS_SERVER_H

#define ACTIVE 0
#define INACTIVE 1
#define OK 0
#define ERROR 1
#define INITIAL_ID 1

enum /*Match Status*/ {
    MATCH_WAITING = 0,
    MATCH_ALIVE,
    MATCH_OVER,
};

#define FRAME_TIME 1.0f

#endif
