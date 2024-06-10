#include "enemy.h"

#include "../constants_game.h"

#include "bullet.h"
#include "rabbit.h"

#define POINTS_KILLING_ENEMY 300
#define ENEMY_SPEED 1
#define ENEMY_MOVE_RANGE 40

Enemy::Enemy(int id, int type, int init_pos_x, int init_pos_y, PhysicalMap& map):
        id(id),
        direction(LEFT),
        enemy_type(type),
        Character(ENEMY_WIDTH_DEFAULT, ENEMY_HEIGHT_DEFAULT, init_pos_x, init_pos_y, map,
                  ENEMY_INITIAL_HEALTH),
        damage(1),
        position_iterator(ENEMY_MOVE_RANGE / 2) {}

void Enemy::receive_damage(int damage) { health -= damage; }

void Enemy::on_colision_with(PhysicalObject* object) { object->on_colision_with_enemy(this); }

void Enemy::on_colision_with_rabbit(Rabbit* rabbit) { rabbit->colided_with_enemy(this, damage); }

void Enemy::hit_by_bullet(Bullet* bullet, int damage) {
    if (is_killed_by_taking_damage(damage)) {
        bullet->bullet_killed_target(POINTS_KILLING_ENEMY);
        kill();
    }
}

void Enemy::hit_by_rabbit_specialattack(Rabbit* rabbit, int damage) {
    if (is_killed_by_taking_damage(damage)) {
        rabbit->add_points(POINTS_KILLING_ENEMY);
        kill();
    }
}

bool Enemy::is_killed_by_taking_damage(int damage) {
    bool killed = false;
    if (health > 0) {
        health -= damage;
        if (health <= 0) {
            killed = true;
        }
    }
    return killed;
}

void Enemy::update() {
    int direction_int = 0;
    (direction == LEFT) ? (direction_int = -1) : (direction_int = 1);
    if (position_iterator == 0) {
        position_iterator = ENEMY_MOVE_RANGE * 2;
        direction == LEFT ? direction = RIGHT : direction = LEFT;
    }
    position_iterator--;
    pos_x += ENEMY_SPEED * direction_int;
    Character::update_position();
}

EnemySnapshot Enemy::get_snapshot() {
    return EnemySnapshot(id, direction, enemy_type, pos_x, pos_y);
}
