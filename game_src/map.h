#ifndef MAP_H
#define MAP_H

#include <memory>
#include <string>
#include <vector>

#include "../common_src/snapshots/snapshot.h"
#include "../physics_src/physical_map.h"
#include "entities/bullet.h"
#include "entities/enemy.h"
#include "entities/item.h"
#include "entities/rabbit.h"

#include "dynamic_map.h"

class Map {
private:
    std::string map_name;
    PhysicalMap physical_map;
    DynamicMap dynamic_map;
    std::map<int, std::vector<SpawnPoint>> spawn_points;
    int width;
    int height;
    int max_players;
    int amount_players;

    // Vectores de Entidades
    std::vector<Rabbit*> players;
    std::vector<Enemy*> enemies;
    std::vector<Bullet*> bullets;
    std::vector<Item*> items;

public:
    void check_colision();
    void reap_dead();
    void update();
    void add_player(int PlayerID);
    void add_enemy(Enemy* enemy);
    void add_bullet(Bullet* bullet);
    void add_item(Item* item);

    Map(int width, int height, int amount_players, const std::string& map_name);

    Map() = default;

    void set_name(const std::string& name);

    void set_physical_map(const PhysicalMap& physical_map);

    void set_dynamic_map(const DynamicMap& dynamic_map);

    void set_spawn_points(const std::map<int, std::vector<SpawnPoint>>& spawn_points);

    void set_max_players(int max_players);

    DynamicMap get_dynamic_map() const;

    PhysicalMap get_physical_map() const;

    std::map<int, std::vector<SpawnPoint>> get_spawn_points() const;

    std::shared_ptr<Snapshot> get_snapshot() const;

    std::string get_name() const;

    ~Map();
};

#endif
