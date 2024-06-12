#include "bullet.h"

#include "../../physics_src/physical_map.h"

#include "enemy.h"
#include "rabbit.h"


Bullet::Bullet(int id, int type, int init_pos_x, int init_pos_y, int bullet_speed, int damage,
               int range, Rabbit& sender):
        id(id),
        type(type),
        PhysicalObject(BLOCK_DIVISION / 2, BLOCK_DIVISION / 4, init_pos_x, init_pos_y),
        range(range),
        damage(damage),
        sender(sender) {
    spe_x = bullet_speed;
}

void Bullet::check_colision_with(PhysicalMap& map) {
    map.check_colision_with_map(pos_x, pos_y, width, height, this);
}

void Bullet::on_colision_with_map() { kill(); }

void Bullet::on_colision_with(PhysicalObject* object) { object->on_colision_with_bullet(this); }

void Bullet::on_colision_with_rabbit(Rabbit* rabbit) {
    if (rabbit != &sender) {
        rabbit->hit_by_bullet(this, damage);
        kill();
    }
}

void Bullet::on_colision_with_enemy(Enemy* enemy) {
    enemy->hit_by_bullet(this, damage);
    kill();
}

void Bullet::bullet_killed_target(int amount_points) { sender.add_points(amount_points); }

int Bullet::get_damage() { return damage; }

void Bullet::update() {
    pos_x += spe_x;
    range--;
    if (range <= 0) {
        kill();
    }
}

ProjectileSnapshot Bullet::get_snapshot() { return ProjectileSnapshot(id, type, pos_x, pos_y, 0); }
