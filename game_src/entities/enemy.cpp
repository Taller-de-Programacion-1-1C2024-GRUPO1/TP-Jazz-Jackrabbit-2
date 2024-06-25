#include "enemy.h"

#include "../constants_game.h"
#include "../map.h"

#include "bullet.h"
#include "rabbit.h"


Enemy::Enemy(int id, int type, int init_pos_x, int init_pos_y, int health, int damage,
             int points_when_killed, int revive_time, int drop_amount, int range, int speed,
             PhysicalMap& physical_map, Map& map):
        id(id),
        initial_pos_x(init_pos_x),
        initial_pos_y(init_pos_y),
        initial_position_iterator(range / 2),
        direction(LEFT),
        enemy_type(type),
        map(map),
        is_alive(true),
        revive_cooldown(0),
        Character(ENEMY_WIDTH_DEFAULT, ENEMY_HEIGHT_DEFAULT, init_pos_x, init_pos_y, physical_map,
                  health),
        damage(damage),
        position_iterator(range / 2),
        range(range),
        points_when_killed(points_when_killed),
        revive_time(revive_time),
        drop_amount(drop_amount),
        speed(speed),
        initial_health(health) {}

void Enemy::receive_damage(int damage) { health -= damage; }

void Enemy::on_colision_with(PhysicalObject* object) { object->on_colision_with_enemy(this); }

void Enemy::on_colision_with_rabbit(Rabbit* rabbit) { rabbit->colided_with_enemy(this, damage); }

void Enemy::drop_items() {
    for (int i = 0; i < drop_amount; i++) {
        int random = rand() % (TOTAL_PROBABILITY);
        int position_x = pos_x + ((BLOCK_DIVISION / 2) * i);
        if (random < HOTDOG_DROP_PROBABILITY) {
            map.add_item(new Hotdog(map.get_projectile_id(), position_x, pos_y));
        } else if (random < HAMBURGER_DROP_CONSTANT) {
            map.add_item(new Hamburger(map.get_projectile_id(), position_x, pos_y));
        } else if (random < HEALTHCARROT_DROP_CONSTANT) {
            map.add_item(new HealthCarrot(map.get_projectile_id(), position_x, pos_y));
        } else if (random < COIN_DROP_CONSTANT) {
            map.add_item(new Coin(map.get_projectile_id(), position_x, pos_y));
        } else if (random < GEM_DROP_CONSTANT) {
            map.add_item(new Gem(map.get_projectile_id(), position_x, pos_y));
        } else if (random < ROTTENCHEESE_DROP_CONSTANT) {
            map.add_item(new RottenCheese(map.get_projectile_id(), position_x, pos_y));
        } else if (random < MACHINEGUNAMMO_DROP_CONSTANT) {
            map.add_item(new MachineGunAmmo(map.get_projectile_id(), position_x, pos_y));
        } else if (random < SNIPERAMMO_DROP_CONSTANT) {
            map.add_item(new SniperAmmo(map.get_projectile_id(), position_x, pos_y));
        } else if (random < RAYGUNAMMO_DROP_CONSTANT) {
            map.add_item(new RayGunAmmo(map.get_projectile_id(), position_x, pos_y));
        } else if (random < NOTHING_DROP_CONSTANT) {
            // DROP NOTHING
        } else {
            // IF CODE GETS HERE ITS AN ERROR, DROP NOTHING
        }
    }
}

void Enemy::kill_enemy() {
    is_alive = false;
    revive_cooldown = revive_time;
    drop_items();
    pos_x = 0;
    pos_y = 0;
}

void Enemy::hit_by_bullet(Bullet* bullet, int damage) {
    if (is_killed_by_taking_damage(damage)) {
        bullet->bullet_killed_target(points_when_killed);
        kill_enemy();
    }
}

void Enemy::hit_by_rabbit_specialattack(Rabbit* rabbit, int damage) {
    if (is_killed_by_taking_damage(damage)) {
        rabbit->add_points(points_when_killed);
        kill_enemy();
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
    if (!is_alive) {
        revive_cooldown--;
        if (revive_cooldown == 0) {
            revive();
        }
    } else {
        int direction_int = 0;
        (direction == LEFT) ? (direction_int = -1) : (direction_int = 1);
        if (position_iterator <= 0) {
            position_iterator = range;
            direction == LEFT ? direction = RIGHT : direction = LEFT;
        }
        position_iterator--;
        spe_x = (speed * direction_int);
        Character::update_position();
    }
}

void Enemy::revive() {
    pos_x = initial_pos_x;
    pos_y = initial_pos_y;
    health = initial_health;
    position_iterator = initial_position_iterator;
    is_alive = true;
}

EnemySnapshot Enemy::get_snapshot() {
    if (is_alive) {
        return EnemySnapshot(id, direction, enemy_type, pos_x, pos_y);
    } else {
        // NECESITAMOS QUE NULL_ENEMY SE PROCESSE
        return EnemySnapshot(id, direction, NULL_ENEMY, pos_x, pos_y);
    }
}

EnemyCrab::EnemyCrab(int id, int init_pos_x, int init_pos_y, PhysicalMap& physical_map, Map& map):
        Enemy(id, CRAB, init_pos_x, init_pos_y, CRAB_HEALTH, CRAB_DAMAGE, CRAB_POINTS,
              CRAB_REVIVE_SECONDS * UPDATE_RATE, CRAB_DROP_AMOUNT,
              (CRAB_BLOCKS_RANGE * BLOCK_DIVISION) / CRAB_SPEED, CRAB_SPEED, physical_map, map) {}

EnemyLizard::EnemyLizard(int id, int init_pos_x, int init_pos_y, PhysicalMap& physical_map,
                         Map& map):
        Enemy(id, LIZARD, init_pos_x, init_pos_y, LIZARD_HEALTH, LIZARD_DAMAGE, LIZARD_POINTS,
              LIZARD_REVIVE_SECONDS * UPDATE_RATE, LIZARD_DROP_AMOUNT,
              LIZARD_BLOCKS_RANGE * BLOCK_DIVISION / LIZARD_SPEED, LIZARD_SPEED, physical_map,
              map) {}

EnemyTurtle::EnemyTurtle(int id, int init_pos_x, int init_pos_y, PhysicalMap& physical_map,
                         Map& map):
        Enemy(id, TURTLE, init_pos_x, init_pos_y, TURTLE_HEALTH, TURTLE_DAMAGE, TURTLE_POINTS,
              TURTLE_REVIVE_SECONDS * UPDATE_RATE, TURTLE_DROP_AMOUNT,
              TURTLE_BLOCKS_RANGE * BLOCK_DIVISION / TURTLE_SPEED, TURTLE_SPEED, physical_map,
              map) {}
