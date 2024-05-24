#ifndef BULLET_H
#define BULLET_H

#include "physical_objects.h"

class Bullet: public PhysicalObject {
private:
    const int damage;

public:
    Bullet(int init_pos_x, int init_pos_y, int bullet_speed, int damage):
            PhysicalObject(BLOCK_DIVISION, BLOCK_DIVISION / 4, init_pos_x, init_pos_y),
            damage(damage) {
        spe_x = bullet_speed;
    }

    void update() { pos_x += spe_x * DELTA_TIME; }

    /*
    void check_colision (Player& player){
        player.check_colision_with_bullet(pos_x, pos_y, width, height, damage);
    };

    void check_colision (Enemy& enemy){
        enemy.check_colision_with_bullet(pos_x, pos_y, width, height, damage);
    };
    */
};

#endif
