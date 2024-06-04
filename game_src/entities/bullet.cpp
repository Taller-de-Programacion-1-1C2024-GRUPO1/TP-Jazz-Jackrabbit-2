#include "bullet.h"

#include "rabbit.h"

Bullet::Bullet(int init_pos_x, int init_pos_y, int bullet_speed, int damage, Rabbit& sender):
        PhysicalObject(BLOCK_DIVISION, BLOCK_DIVISION / 4, init_pos_x, init_pos_y),
        damage(damage),
        sender(sender) {
    spe_x = bullet_speed;
}

void Bullet::update() { pos_x += spe_x * DELTA_TIME; }

/*
void Bullet::check_colision (Rabbit& player){
    player.check_colision_with_bullet(pos_x, pos_y, width, height, damage);
};

void Bullet::check_colision (Enemy& enemy){
    enemy.check_colision_with_bullet(pos_x, pos_y, width, height, damage);
};

*/
