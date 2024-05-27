#ifndef SUPPLY_SNAPSHOT_H
#define SUPPLY_SNAPSHOT_H

#include "../../game_src/constants_game.h"

class SupplySnapshot {
public:
    SupplyType type;
    int pos_x;
    int pos_y;
    char id;
    SupplyState state;
    int width;
    int height;

    SupplySnapshot(SupplyType type, int pos_x, int pos_y, char id, SupplyState state, int width,
                   int height):
            type(type),
            pos_x(pos_x),
            pos_y(pos_y),
            id(id),
            state(state),
            width(width),
            height(height) {}
};

#endif
