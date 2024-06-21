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

    void add_bullet_to_map(int pos_x, int pos_y, int direction, int type, int cooldown);

    void execute_max_ammo();
    void update();
    int get_ammo();
    bool can_fire();
    void reset_ammo_amount();
    void add_ammo(int amount_ammo);
    virtual ~Gun() = default;
};


class BasicGun: public Gun {

public:
    BasicGun(Rabbit& owner, Map& manager);
    bool has_ammo() override;
    void fire(int pos_x, int pos_y, int direction) override;
};


class FlameThrower: public Gun {
public:
    FlameThrower(Rabbit& owner, Map& manager);
    bool has_ammo() override;
    void fire(int pos_x, int pos_y, int direction) override;
};


class RocketLauncher: public Gun {
public:
    RocketLauncher(Rabbit& owner, Map& manager);
    bool has_ammo() override;
    void fire(int pos_x, int pos_y, int direction) override;
};

class RayGun: public Gun {
public:
    RayGun(Rabbit& owner, Map& manager);
    bool has_ammo() override;
    void fire(int pos_x, int pos_y, int direction) override;
};

#endif
