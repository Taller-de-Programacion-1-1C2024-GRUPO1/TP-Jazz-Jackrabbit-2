#ifndef ITEM_H
#define ITEM_H

#include "../../common_src/snapshots/snapshot_supply.h"
#include "../../physics_src/physical_objects.h"
#include "../constants_game.h"
class Rabbit;


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


class MachineGunAmmo: public Item {
public:
    MachineGunAmmo(int id, int init_pos_x, int init_pos_y);
    void on_colision_with_rabbit(Rabbit* rabbit) override;
};

class SniperAmmo: public Item {
public:
    SniperAmmo(int id, int init_pos_x, int init_pos_y);
    void on_colision_with_rabbit(Rabbit* rabbit) override;
};

class HealthCarrot: public Item {
public:
    HealthCarrot(int id, int init_pos_x, int init_pos_y);
    void on_colision_with_rabbit(Rabbit* rabbit) override;
};
class Hotdog: public Item {
public:
    Hotdog(int id, int init_pos_x, int init_pos_y);
    void on_colision_with_rabbit(Rabbit* rabbit) override;
};
class Hamburger: public Item {
public:
    Hamburger(int id, int init_pos_x, int init_pos_y);
    void on_colision_with_rabbit(Rabbit* rabbit) override;
};
class RottenCheese: public Item {
public:
    RottenCheese(int id, int init_pos_x, int init_pos_y);
    void on_colision_with_rabbit(Rabbit* rabbit) override;
};

class RayGunAmmo: public Item {
public:
    RayGunAmmo(int id, int init_pos_x, int init_pos_y);
    void on_colision_with_rabbit(Rabbit* rabbit) override;
};


#endif
