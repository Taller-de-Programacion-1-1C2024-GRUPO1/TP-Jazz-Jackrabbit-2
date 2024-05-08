#include "enemy.h"


Enemy::Enemy(): is_alive(true), num_of_iterations_dead(0) {}


bool Enemy::enemy_is_alive() const { return is_alive; }


void Enemy::kill() { is_alive = false; }


bool Enemy::try_resurrect() {
    if (!is_alive) {
        num_of_iterations_dead++;
        if (this->num_of_iterations_dead >= NUM_OF_ITERATIONS_TO_RESURRECT) {
            is_alive = true;
            num_of_iterations_dead = 0;
            return true;
        }
    }
    return false;
}


Enemies::Enemies(int num_of_enemies):
        num_of_enemies(num_of_enemies), enemies(), num_alive_enemies(num_of_enemies) {
    for (int i = 0; i < num_of_enemies; i++) {
        enemies.push_back(Enemy());
    }
}


bool Enemies::try_kill_enemy() {
    auto aliveEnemyIter =
            std::find_if(enemies.begin(), enemies.end(), std::mem_fn(&Enemy::enemy_is_alive));
    if (aliveEnemyIter != enemies.end()) {
        aliveEnemyIter->kill();
        num_alive_enemies--;
        std::cout << "Un enemigo ha muerto. " << num_alive_enemies << " vivo(s) y "
                  << num_of_enemies - num_alive_enemies << " muerto(s)." << std::endl;
        return true;
    }
    return false;
}


int Enemies::try_resurrect_enemies() {
    int num_of_resurrected = 0;
    for (auto& enemy: enemies) {
        if (enemy.try_resurrect()) {
            num_alive_enemies++;
            num_of_resurrected++;
            std::cout << "Un enemigo ha revivido. " << num_alive_enemies << " vivo(s) y "
                      << num_of_enemies - num_alive_enemies << " muerto(s)." << std::endl;
        }
    }
    return num_of_resurrected;
}

uint16_t Enemies::get_num_alive_enemies() const { return num_alive_enemies; }


uint16_t Enemies::get_num_of_dead_enemies() const { return num_of_enemies - num_alive_enemies; }
