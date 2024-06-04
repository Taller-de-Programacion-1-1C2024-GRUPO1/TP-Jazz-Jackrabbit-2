#ifndef BULLET_H
#define BULLET_H

#include "../../physics_src/physical_objects.h"
class Rabbit;
class PhysicalMap;

class Bullet: public PhysicalObject {
private:
    const int damage;
    Rabbit& sender;

public:
    Bullet(int init_pos_x, int init_pos_y, int bullet_speed, int damage, Rabbit& sender);

    void update();

    void check_colision_with(PhysicalMap& map);
    void on_colision_with_map();

    void on_colision_with(PhysicalObject* object) override;
    void on_colision_with_rabbit(Rabbit* rabbit) override;
    void on_colision_with_enemy(Enemy* enemy) override;

    void bullet_killed_target(int amount_points);
    int get_damage();
};

#endif
