#ifndef GUN_H
#define GUN_H

class Map;
class Rabbit;


class Gun {
protected:
    int ammo;
    int max_ammo;

    Map& manager;
    Rabbit& owner;

    int damage;
    int fire_cooldown;
    int range;
    int bullet_speed;

public:
    Gun(int max_ammo, int damage, int range, int bullet_speed, Rabbit& owner, Map& manager);

    virtual bool has_ammo() = 0;
    virtual void fire(int pos_x, int pos_y, int direction) = 0;

    void update();
    int get_ammo();
    bool can_fire();

    void add_ammo(int amount_ammo);
};

#define BASIC_GUN_FIRE_COOLDOWN 20
#define BASIC_GUN_MAX_AMMO 999
#define BASIC_GUN_DAMAGE 1
#define BASIC_GUN_RANGE 100
#define BASIC_GUN_BULLET_SPEED 10

class BasicGun: public Gun {

public:
    BasicGun(Rabbit& owner, Map& manager);
    bool has_ammo() override;
    void fire(int pos_x, int pos_y, int direction) override;
};

#define MACHINEGUN_FIRE_COOLDOWN BASIC_GUN_FIRE_COOLDOWN / 4
#define MACHINEGUN_MAX_AMMO 300
#define MACHINEGUN_DAMAGE BASIC_GUN_DAMAGE
#define MACHINEGUN_RANGE BASIC_GUN_RANGE
#define MACHINEGUN_BULLET_SPEED BASIC_GUN_BULLET_SPEED

class MachineGun: public Gun {
public:
    MachineGun(Rabbit& owner, Map& manager);
    bool has_ammo() override;
    void fire(int pos_x, int pos_y, int direction) override;
};

#define SNIPER_FIRE_COOLDOWN BASIC_GUN_FIRE_COOLDOWN
#define SNIPER_MAX_AMMO 10
#define SNIPER_DAMAGE BASIC_GUN_DAMAGE * 3
#define SNIPER_RANGE BASIC_GUN_RANGE * 3
#define SNIPER_BULLET_SPEED BASIC_GUN_BULLET_SPEED * 2

class Sniper: public Gun {
public:
    Sniper(Rabbit& owner, Map& manager);
    bool has_ammo() override;
    void fire(int pos_x, int pos_y, int direction) override;
};

#endif
