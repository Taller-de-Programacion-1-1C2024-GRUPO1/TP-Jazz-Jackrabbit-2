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

class Map {
private:
    std::string map_name;
    // PhysicalMap physical_map;
    int width;
    int height;
    int amount_players;

    //Vectores de Entidades
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
    
    void set_physical_map(const PhysicalMap& physical_map);

    std::shared_ptr<Snapshot> get_snapshot() const;

    std::string get_name() const;

    ~Map();
};

#endif
