#ifndef ITEM_H
#define ITEM_H

#include "../../common_src/snapshots/snapshot_supply.h"
#include "../../physics_src/physical_objects.h"
#include "../constants_game.h"
class Rabbit;
#define COIN_POINTS 100
#define GEM_POINTS 200

class Item: public PhysicalObject {
    int id;
    int type;

public:
    Item(int id, int type, int init_pos_x, int init_pos_y);
    void on_colision_with(PhysicalObject* object) override {}
    virtual void on_colision_with_rabbit(Rabbit* rabbit) override {}
    SupplySnapshot get_snapshot();
    virtual ~Item() = default;
};

class Coin: public Item {
public:
    Coin(int id, int init_pos_x, int init_pos_y);
    void on_colision_with_rabbit(Rabbit* rabbit) override;
};

class Gem: public Item {
public:
    Gem(int id, int init_pos_x, int init_pos_y);
    void on_colision_with_rabbit(Rabbit* rabbit) override;
};


class Ammo: public Item {
public:
    Ammo(int id, int init_pos_x, int init_pos_y);
};

#endif
