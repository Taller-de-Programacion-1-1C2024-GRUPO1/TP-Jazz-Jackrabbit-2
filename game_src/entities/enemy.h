#ifndef ENEMY_H
#define ENEMY_H

#include "../../common_src/snapshots/snapshot_enemy.h"

#include "character.h"
class Enemy: public Character {
private:
    // MODIFICACION DE POSICION

    int damage;
    int id;
    int direction;
    int enemy_type;
    int position_iterator;

public:
    Enemy(int id, int type, int init_pos_x, int init_pos_y, PhysicalMap& map);


    void receive_damage(int damage) override;
    // COLISIONES CON ENTIDADES
    void on_colision_with(PhysicalObject* object) override;
    void on_colision_with_rabbit(Rabbit* rabbit) override;

    void hit_by_rabbit_specialattack(Rabbit* rabbit, int damage);
    void hit_by_bullet(Bullet* bullet, int damage);
    bool is_killed_by_taking_damage(int damage);
    void update();
    EnemySnapshot get_snapshot();
};

#endif
