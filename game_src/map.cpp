#include "map.h"

Map::Map(int width, int height, int amount_players, const std::string& map_name):
        map_name(map_name), width(width), height(height), amount_players(amount_players) {}


void Map::check_colision() {}

void Map::update() {
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
void Map::reap_dead() {
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


void Map::add_player(int PlayerID) {
    // players.insert(players.begin()+PlayerID, new Rabbit(0/*SPAWN X*/,0/*SPAWN Y*/,/*MAP*/));
}

void Map::add_enemy(Enemy* enemy) { enemies.push_back(enemy); }

void Map::add_bullet(Bullet* bullet) { bullets.push_back(bullet); }

void Map::add_item(Item* item) { items.push_back(item); }

void Map::set_physical_map(const PhysicalMap& physical_map) { this->physical_map = physical_map; }

void Map::set_dynamic_map(const DynamicMap& dynamic_map) { this->dynamic_map = dynamic_map; }

void Map::set_max_players(int max_players) { this->max_players = max_players; }

std::shared_ptr<Snapshot> Map::get_snapshot() const {
    Snapshot snapshot({}, {}, {});
    snapshot.set_dimensions(height, width, RABBIT_HEIGHT_DEFAULT, RABBIT_WIDTH_DEFAULT,
                            amount_players);
    return std::make_shared<Snapshot>(snapshot);
}

std::string Map::get_name() const { return map_name; }

Map::~Map() {}
