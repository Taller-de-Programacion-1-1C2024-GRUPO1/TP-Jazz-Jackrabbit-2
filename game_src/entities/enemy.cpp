#include "enemy.h"

#include "../constants_game.h"

#include "bullet.h"
#include "rabbit.h"

#define POINTS_KILLING_ENEMY 300

Enemy::Enemy(int id, int type, int init_pos_x, int init_pos_y, PhysicalMap& map):
        id(id),
        direction(LEFT),
        enemy_type(type),
        Character(ENEMY_WIDTH_DEFAULT, ENEMY_HEIGHT_DEFAULT, init_pos_x,
                  init_pos_y, map, ENEMY_INITIAL_HEALTH),
        acc_y(GRAVITY),
        damage(1) {}

void Enemy::receive_damage(int damage) { health -= damage; }

void Enemy::on_colision_with(PhysicalObject* object) { object->on_colision_with_enemy(this); }

void Enemy::on_colision_with_rabbit(Rabbit* rabbit) { rabbit->receive_damage(damage); }

void Enemy::hit_by_bullet(Bullet* bullet, int damage) {
    if (is_killed_by_taking_damage(damage)) {
        bullet->bullet_killed_target(POINTS_KILLING_ENEMY);
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
    check_colision_with_map();
    // GRAVITY
    if (!on_floor && spe_y < MAX_FALLING_SPEED) {
        spe_y += acc_y;
    }
    // ACTUALIZA POSICIONES
    pos_x += spe_x;
    pos_y += spe_y;

    // REPOSITION
    check_colision_with_map();
    if (on_floor) {
        if (!on_left_slope && !on_right_slope) {
            pos_y = pos_y - ((pos_y % BLOCK_DIVISION));
        }
        spe_y = 0;
    }
    if (on_roof) {
        pos_y = pos_y + (BLOCK_DIVISION - (pos_y % BLOCK_DIVISION));
        spe_y = 0;
    }
    if (on_left_wall) {
        pos_x = pos_x + (BLOCK_DIVISION - (pos_x % BLOCK_DIVISION));
    }
    if (on_right_wall) {
        pos_x = pos_x - (pos_x % BLOCK_DIVISION);
    }

    check_colision_with_map();
    if (on_right_slope) {
        if (spe_x > 0) {
            pos_y -= spe_x;
        }
    } else if (on_left_slope) {
        if (spe_x < 0) {
            pos_y += spe_x;
        }
    }

    // NO HAY INERCIA EN EJE X
    spe_x = 0;
}

EnemySnapshot Enemy::get_snapshot() {
    return EnemySnapshot(id, direction, enemy_type, pos_x, pos_y);
}
