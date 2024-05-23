#ifndef SUPPLY_SNAPSHOT_H
#define SUPPLY_SNAPSHOT_H

#include "../../game_src/constants_game.h"

class SupplySnapshot {
public:
    SupplyType type;
    float pos_x;
    float pos_y;
    char id;
    SupplyState state;
    float width;
    float height;

    SupplySnapshot(SupplyType type, float pos_x, float pos_y, char id, SupplyState state,
                   float width, float height):
            type(type),
            pos_x(pos_x),
            pos_y(pos_y),
            id(id),
            state(state),
            width(width),
            height(height) {}
};

#endif
