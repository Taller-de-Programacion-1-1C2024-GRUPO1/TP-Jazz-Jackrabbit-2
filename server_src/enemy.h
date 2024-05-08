#ifndef ENEMY_H
#define ENEMY_H
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../common_src/utils.h"

class Enemy {
private:
    bool is_alive;
    int num_of_iterations_dead;


public:
    Enemy();
    bool enemy_is_alive() const;
    void kill();
    bool try_resurrect();
};


class Enemies {
private:
    uint16_t num_of_enemies;
    std::vector<Enemy> enemies;
    uint16_t num_alive_enemies;

public:
    explicit Enemies(int num_of_enemies);
    bool try_kill_enemy();
    int try_resurrect_enemies();
    uint16_t get_num_alive_enemies() const;
    uint16_t get_num_of_dead_enemies() const;
};

#endif
