#ifndef MAP_H
#define MAP_H

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../common_src/snapshots/snapshot.h"
#include "../physics_src/physical_map.h"
#include "commands/command.h"
#include "entities/bullet.h"
#include "entities/enemy.h"
#include "entities/item.h"
#include "entities/rabbit.h"

#include "dynamic_map.h"
#include "spawn_point.h"

class Map {
private:
    std::string map_name;
    PhysicalMap physical_map;
    DynamicMap dynamic_map;
    std::map<int, std::vector<SpawnPoint>> spawn_points;
    int width;
    int height;
    int texture_id;
    int max_players;
    int amount_players;
    int projectile_id;

    // Vectores de Entidades
    std::vector<Rabbit*> players;
    std::vector<Enemy*> enemies;
    std::vector<Bullet*> bullets;
    std::vector<Item*> items;

    std::vector<RabbitSnapshot> get_rabbit_snapshot();

    std::vector<ProjectileSnapshot> get_projectile_snapshot();

    std::vector<SupplySnapshot> get_supply_snapshot();

    std::vector<EnemySnapshot> get_enemy_snapshot();

public:
    void check_colision();
    void reap_dead();
    void update();
    void add_player(int PlayerID, ChampionType champion, const std::string& player_name);
    void add_enemy(Enemy* enemy);
    void add_bullet(Bullet* bullet);
    void add_item(Item* item);
    int get_projectile_id();

    Map(int width, int height, int texture_id, int max_players, const std::string& map_name,
        const PhysicalMap& physical_map, const DynamicMap& dynamic_map,
        const std::map<int, std::vector<SpawnPoint>>& spawn_points);


    void set_amount_players(int amount_players);

    std::string get_name() const;

    PhysicalMap get_physical_map() const;

    DynamicMap get_dynamic_map() const;

    std::map<int, std::vector<SpawnPoint>> get_spawn_points() const;

    int get_amount_players();

    int get_texture_id();

    int get_max_players();

    int get_width();

    int get_height();

    void create_entities();

    Snapshot get_snapshot(uint32_t match_time);

    Snapshot get_init_snapshot();

    int get_rabbit_position_by_id(int id);

    void add_command(std::shared_ptr<Command> command);

    ~Map();
};

#endif
