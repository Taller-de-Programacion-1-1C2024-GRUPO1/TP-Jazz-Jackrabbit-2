#include "manager.h"

Manager::Manager(PhysicalMap& map): gameMap(map) {}

void Manager::check_colision() {}

void Manager::update() {
    for (auto player: players) {
        player->update();
    }
    for (auto enemy: enemies) {
        enemy->update();
    }
    for (auto bullet: bullets) {
        bullet->update();
    }
    check_colision();
    reap_dead();
}


// FALTA HACER DELETE SI SE USA HEAP
void Manager::reap_dead() {
    for (int i = 0; i < players.size(); i++) {
        if (players[i]->is_dead()) {
            players.erase(players.begin() + i);
        }
    }
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->is_dead()) {
            enemies.erase(enemies.begin() + i);
        }
    }
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i]->is_dead()) {
            bullets.erase(bullets.begin() + i);
        }
    }
    for (int i = 0; i < items.size(); i++) {
        if (items[i]->is_dead()) {
            items.erase(items.begin() + i);
        }
    }
}

void Manager::render(SDL_Renderer* renderer) {
    gameMap.render(renderer);
    for (auto player: players) {
        player->render(renderer);
    }
    for (auto enemy: enemies) {
        enemy->render(renderer);
    }

    /*
    for (auto bullet : bullets){
        bullet->render(renderer);
    }
    for (auto item : items){
        item->render(renderer);
    }
    */
}


void Manager::add_player(Rabbit* player) { players.push_back(player); }

void Manager::add_enemy(Enemy* enemy) { enemies.push_back(enemy); }

void Manager::add_bullet(Bullet* bullet) { bullets.push_back(bullet); }

void Manager::add_item(Item* item) { items.push_back(item); }
