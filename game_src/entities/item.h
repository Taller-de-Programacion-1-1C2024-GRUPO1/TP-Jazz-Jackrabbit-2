#ifndef ITEM_H
#define ITEM_H

#include "../../physics_src/physical_objects.h"

class Rabbit;
#define COIN_POINTS 100
#define GEM_POINTS 200

class Item: public PhysicalObject {
public:
    Item(int init_pos_x, int init_pos_y);
    void on_colision_with(PhysicalObject* object) override {}
    virtual void on_colision_with_rabbit(Rabbit* rabbit) override {}
};


class Coin: public Item {
public:
    Coin(int init_pos_x, int init_pos_y);
    void on_colision_with_rabbit(Rabbit* rabbit) override;
};

class Gem: public Item {
public:
    Gem(int init_pos_x, int init_pos_y);
    void on_colision_with_rabbit(Rabbit* rabbit) override;
};


class Ammo: public Item {
public:
    Ammo(int init_pos_x, int init_pos_y);
};

#endif
