#ifndef ITEM_H
#define ITEM_H

#include "../../physics_src/physical_objects.h"

class Item: public PhysicalObject {
public:
    Item(int init_pos_x, int init_pos_y):
            PhysicalObject(BLOCK_DIVISION, BLOCK_DIVISION, init_pos_x, init_pos_y) {}
};

class Coin: public Item {
public:
    Coin(int init_pos_x, int init_pos_y): Item(init_pos_x, init_pos_y) {}
};

class Gem: public Item {
public:
    Gem(int init_pos_x, int init_pos_y): Item(init_pos_x, init_pos_y) {}
};


class Ammo: public Item {
public:
    Ammo(int init_pos_x, int init_pos_y): Item(init_pos_x, init_pos_y) {}
};

#endif
