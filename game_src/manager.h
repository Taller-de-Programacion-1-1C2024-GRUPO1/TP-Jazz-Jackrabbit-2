#ifndef MANAGER_H
#define MANAGER_H
#include <vector>

#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/bullet.h"
#include "entities/item.h"
#include "../physics_src/physical_map.h"


class Manager {
private: 
    std::vector<Player*> players;
    std::vector<Enemy*> enemies;
    std::vector<Bullet*> bullets;
    std::vector<Item*> items;
    PhysicalMap gameMap;


    void check_colision();

public:
    explicit Manager(PhysicalMap map);
    void update();
    void render(SDL_Renderer* renderer);
    void add_player(Player* player);
    void add_enemy(Enemy* enemy);
    void add_bullet(Bullet* bullet);
    void add_item(Item* item);

};

#endif