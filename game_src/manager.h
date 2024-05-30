#ifndef MANAGER_H
#define MANAGER_H
#include <vector>

#include "../physics_src/physical_map.h"
#include "entities/bullet.h"
#include "entities/enemy.h"
#include "entities/item.h"
#include "entities/rabbit.h"


class Manager {
private:
    std::vector<Rabbit*> players;
    std::vector<Enemy*> enemies;
    std::vector<Bullet*> bullets;
    std::vector<Item*> items;
    PhysicalMap& gameMap;


    void check_colision();
    void reap_dead();

public:
    explicit Manager(PhysicalMap& map);
    void update();
    void render(SDL_Renderer* renderer);
    void add_player(Rabbit* player);
    void add_enemy(Enemy* enemy);
    void add_bullet(Bullet* bullet);
    void add_item(Item* item);
};

#endif
