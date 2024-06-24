#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <queue>
#include <string>
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
    int max_health;
    const int spawn_x;
    const int spawn_y;
    Map& map;
    std::vector<Gun*> gun_inventory;
    int current_gun;
    State* state;
    int direction;
    std::queue<std::shared_ptr<Command>> events_queue;
    bool state_needs_change;
    int next_state;
    std::string player_name;

public:
    Rabbit(uint8_t champion_type, int init_pos_x, int init_pos_y, PhysicalMap& physical_map,
           Map& map);

    void set_rabbit_info(int id, uint8_t champion_type, const std::string& player_name);
    int get_rabbit_id();
    void update();
    void update_action();
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
    void change_weapon();

    // SHOOT
    void set_action_shoot();
    void add_machinegun_ammo(int amount_ammo);
    void add_sniper_ammo(int amount_ammo);
    void add_raygun_ammo(int amount_ammo);

    // COLISION
    void on_colision_with(PhysicalObject* object) override;
    // void on_colision_with_bullet(Bullet* bullet);
    void colided_with_enemy(Enemy* object, int damage);
    void on_colision_with_rabbit(Rabbit* object) override;
    void hit_by_bullet(Bullet* bullet, int damage);


    // COLIDED
    bool is_killed_by_taking_damage(int damage);
    void receive_damage(int damage) override;
    void add_points(int amount_of_points);
    void add_health(int amount_of_health);

    // TESTING

    void imprimir_posicion();

    void add_command(std::shared_ptr<Command> command);

    // ESTADOS
    void set_state(int state);
    void set_intoxicated();
    void set_alive();
    void set_godmode();
    void change_state();


    void execute_jump();
    void execute_run_right();
    void execute_run_fast_right();
    void execute_run_left();
    void execute_run_fast_left();
    void execute_shoot();
    void execute_change_weapon();

    // SNAPSHOTS
    RabbitSnapshot get_snapshot();

    // SPECIAL ATTACKS
    void special_attack_jazz();
    void special_attack_spaz(int direction);
    void special_attack_lori();
    void execute_special_spaz(int direction);
    void execute_special_jazz();
    void execute_special_lori();

    // CHEATS
    void receive_max_ammo();
    void receive_max_health();
    void receive_god_mode();
    void respawn();

    Rabbit(const Rabbit&) = delete;
    Rabbit& operator=(const Rabbit&) = delete;
    ~Rabbit();
};

#endif
