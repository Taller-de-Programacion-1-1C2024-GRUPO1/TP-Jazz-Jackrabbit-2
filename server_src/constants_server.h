#ifndef CONSTANTS_SERVER_H
#define CONSTANTS_SERVER_H

#define ACTIVE 0
#define INACTIVE 1
#define INITIAL_ID 1

enum /*Match Status*/ {
    MATCH_WAITING = 0,
    MATCH_ALIVE,
    MATCH_OVER,
};

#define FPS 60
#define FRAME_DELAY (1000 / FPS)

#endif
