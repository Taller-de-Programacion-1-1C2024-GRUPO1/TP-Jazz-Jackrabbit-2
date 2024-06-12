#ifndef SUPPLY_SNAPSHOT_H
#define SUPPLY_SNAPSHOT_H

#include "../../game_src/constants_game.h"

class SupplySnapshot {
public:
    int id;
    int supply_type;
    int pos_x;
    int pos_y;

    SupplySnapshot(int id, int supply_type, int pos_x, int pos_y):
            id(id), supply_type(supply_type), pos_x(pos_x), pos_y(pos_y) {}
};

#endif
