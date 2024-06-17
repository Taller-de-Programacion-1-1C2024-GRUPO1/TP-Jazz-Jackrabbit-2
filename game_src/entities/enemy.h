#ifndef ENEMY_H
#define ENEMY_H

#include "../../common_src/snapshots/snapshot_enemy.h"

#include "character.h"

class Map;

class Enemy: public Character {
private:
    // MODIFICACION DE POSICION

    int damage;
    int id;
    int initial_pos_x;
    int initial_pos_y;
    int direction;
    int enemy_type;
    int position_iterator;
    int initial_position_iterator;
    bool is_alive;
    int revive_cooldown;
    int points_when_killed;
    int revive_time;
    int drop_amount;
    int speed;
    int range;
    int initial_health;

    Map& map;

public:
    Enemy(int id, int type, int init_pos_x, int init_pos_y, int health, int damage,
          int points_when_killed, int revive_time, int drop_amount, int range, int speed,
          PhysicalMap& physical_map, Map& map);

    void revive();
    void receive_damage(int damage) override;
    // COLISIONES CON ENTIDADES
    void on_colision_with(PhysicalObject* object) override;
    void on_colision_with_rabbit(Rabbit* rabbit) override;

    void hit_by_rabbit_specialattack(Rabbit* rabbit, int damage);
    void hit_by_bullet(Bullet* bullet, int damage);
    bool is_killed_by_taking_damage(int damage);
    void kill_enemy();
    void update();
    void drop_items();
    EnemySnapshot get_snapshot();
    virtual ~Enemy() = default;
};

class EnemyCrab: public Enemy {
public:
    EnemyCrab(int id, int init_pos_x, int init_pos_y, PhysicalMap& physical_map, Map& map);
};

class EnemyLizard: public Enemy {
public:
    EnemyLizard(int id, int init_pos_x, int init_pos_y, PhysicalMap& physical_map, Map& map);
};

class EnemyTurtle: public Enemy {
public:
    EnemyTurtle(int id, int init_pos_x, int init_pos_y, PhysicalMap& physical_map, Map& map);
};

#endif
