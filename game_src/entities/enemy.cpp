#include "enemy.h"

#include "../constants_game.h"
#include "../map.h"

#include "bullet.h"
#include "rabbit.h"


Enemy::Enemy(int id, int type, int init_pos_x, int init_pos_y, PhysicalMap& physical_map, Map& map):
        id(id),
        initial_pos_x(init_pos_x),
        initial_pos_y(init_pos_y),
        initial_position_iterator(ENEMY_MOVE_RANGE / 2),
        direction(LEFT),
        enemy_type(type),
        map(map),
        is_alive(true),
        revive_cooldown(0),
        Character(ENEMY_WIDTH_DEFAULT, ENEMY_HEIGHT_DEFAULT, init_pos_x, init_pos_y, physical_map,
                  ENEMY_INITIAL_HEALTH),
        damage(1),
        position_iterator(ENEMY_MOVE_RANGE / 2) {}

void Enemy::receive_damage(int damage) { health -= damage; }

void Enemy::on_colision_with(PhysicalObject* object) { object->on_colision_with_enemy(this); }

void Enemy::on_colision_with_rabbit(Rabbit* rabbit) { rabbit->colided_with_enemy(this, damage); }

void Enemy::drop_items() {
    int random = rand() % 100;
    if (random < 10) {
        std::cout << "Dropping hotdog" << std::endl;
        map.add_item(new Hotdog(map.get_projectile_id(), pos_x, pos_y));
    } else if (random < 20) {
        std::cout << "Dropping hamburger" << std::endl;
        map.add_item(new Hamburger(map.get_projectile_id(), pos_x, pos_y));
    } else if (random < 30) {
        std::cout << "Dropping carrot" << std::endl;
        map.add_item(new HealthCarrot(map.get_projectile_id(), pos_x, pos_y));
    } else if (random < 40) {
        std::cout << "Dropping cheese" << std::endl;
        map.add_item(new RottenCheese(map.get_projectile_id(), pos_x, pos_y));
    } else if (random < 50) {
        std::cout << "Dropping machine gun ammo" << std::endl;
        map.add_item(new MachineGunAmmo(map.get_projectile_id(), pos_x, pos_y));
    } else if (random < 60) {
        std::cout << "Dropping coin" << std::endl;
        map.add_item(new Coin(map.get_projectile_id(), pos_x, pos_y));
    } else if (random < 70) {
        std::cout << "Dropping sniper ammo" << std::endl;
        map.add_item(new SniperAmmo(map.get_projectile_id(), pos_x, pos_y));
    } else if (random < 80) {
        std::cout << "Dropping gem" << std::endl;
        map.add_item(new Gem(map.get_projectile_id(), pos_x, pos_y));
    }
}

void Enemy::kill_enemy() {
    is_alive = false;
    revive_cooldown = ENEMY_REVIVE_COOLDOWN;
    drop_items();
    pos_x = 0;
    pos_y = 0;
}

void Enemy::hit_by_bullet(Bullet* bullet, int damage) {
    if (is_killed_by_taking_damage(damage)) {
        bullet->bullet_killed_target(POINTS_KILLING_ENEMY);
        kill_enemy();
    }
}

void Enemy::hit_by_rabbit_specialattack(Rabbit* rabbit, int damage) {
    if (is_killed_by_taking_damage(damage)) {
        rabbit->add_points(POINTS_KILLING_ENEMY);
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
        if (position_iterator == 0) {
            position_iterator = ENEMY_MOVE_RANGE * 2;
            direction == LEFT ? direction = RIGHT : direction = LEFT;
        }
        position_iterator--;
        pos_x += ENEMY_SPEED * direction_int;
        Character::update_position();
    }
}

void Enemy::revive() {
    pos_x = initial_pos_x;
    pos_y = initial_pos_y;
    health = ENEMY_INITIAL_HEALTH;
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
        Enemy(id, CRAB, init_pos_x, init_pos_y, physical_map, map) {}

EnemyLizard::EnemyLizard(int id, int init_pos_x, int init_pos_y, PhysicalMap& physical_map,
                         Map& map):
        Enemy(id, LIZARD, init_pos_x, init_pos_y, physical_map, map) {}

EnemyTurtle::EnemyTurtle(int id, int init_pos_x, int init_pos_y, PhysicalMap& physical_map,
                         Map& map):
        Enemy(id, TURTLE, init_pos_x, init_pos_y, physical_map, map) {}
