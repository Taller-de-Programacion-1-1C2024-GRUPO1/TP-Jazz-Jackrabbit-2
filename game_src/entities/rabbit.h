#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <queue>
#include <vector>

#include "../../common_src/snapshots/snapshot_rabbit.h"

#include "character.h"


class Bullet;
class Enemy;
class Item;
class State;
class Map;
class Gun;
class Command;

class Rabbit: public Character {
private:
    int id;
    uint8_t champion_type;
    int points;
    int action;
    const int spawn_x;
    const int spawn_y;
    Map& map;
    std::vector<Gun*> gun_inventory;
    int current_gun;
    State* state;
    int direction;
    std::queue<std::shared_ptr<Command>> events_queue;

public:
    Rabbit(uint8_t champion_type, int init_pos_x, int init_pos_y, PhysicalMap& physical_map,
           Map& map);
    void set_rabbit_id(int id);
    void set_champion(uint8_t champion_type);
    int get_rabbit_id();
    void update();
    void update_action();
    void update_position();
    void update_guns();
    void revive();
    // EVENTS
    void handle_events();

    void jump();
    void run_right();
    void run_fast_right();
    void run_left();
    void run_fast_left();
    void shoot();
    void special_attack();
    void change_weapon();

    // SHOOT
    void set_action_shoot();
    void add_machinegun_ammo(int amount_ammo);
    void add_sniper_ammo(int amount_ammo);

    // COLISION
    void on_colision_with(PhysicalObject* object) override;
    // void on_colision_with_bullet(Bullet* bullet);
    // void on_colision_with_enemy(Enemy* object);
    // void on_colision_with_item(Item* object);
    void hit_by_bullet(Bullet* bullet, int damage);

    bool is_killed_by_taking_damage(int damage);
    void receive_damage(int damage) override;
    void add_points(int amount_of_points);

    // TESTING

    void imprimir_posicion();

    void add_command(std::shared_ptr<Command> command);

    // ESTADOS
    void set_state(State* state);

    void execute_jump();
    void execute_run_right();
    void execute_run_fast_right();
    void execute_run_left();
    void execute_run_fast_left();
    void execute_shoot();
    void execute_special_attack();
    void execute_change_weapon();

    // SNAPSHOTS
    RabbitSnapshot get_snapshot();

    Rabbit(const Rabbit&) = delete;
    Rabbit& operator=(const Rabbit&) = delete;
    ~Rabbit();
};

#endif
