#include "map.h"

Map::Map(int width, int height, int amount_players, const std::string& map_name):
        map_name(map_name), width(width), height(height), amount_players(amount_players) {}


void Map::check_colision() {
    for (auto player: players) {
        for (auto enemy: enemies) {
            player->check_colision_with(enemy);
        }
        for (auto bullet: bullets) {
            player->check_colision_with(bullet);
        }
        for (auto item: items) {
            player->check_colision_with(item);
        }
    }
    for (auto enemy: enemies) {
        for (auto bullet: bullets) {
            enemy->check_colision_with(bullet);
        }
    }
    for (auto bullet: bullets) {
        bullet->check_colision_with(physical_map);
    }
}

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
    int i = 0;
    while (i < enemies.size()) {
        if (enemies[i]->is_dead()) {
            enemies.erase(enemies.begin() + i);
        } else {
            i++;
        }
    }
    i = 0;
    while (i < bullets.size()) {
        if (bullets[i]->is_dead()) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        } else {
            i++;
        }
    }
    i = 0;
    while (i < items.size()) {
        if (items[i]->is_dead()) {
            items.erase(items.begin() + i);
        } else {
            i++;
        }
    }
}


void Map::add_player(int PlayerID, ChampionType champion) {
    /*
    for (auto rabbit: players) {
        // rabbit->set_id(PlayerID);
        // rabbit->set_champion(champion);
    }
    */
}

void Map::add_enemy(Enemy* enemy) { enemies.push_back(enemy); }

void Map::add_bullet(Bullet* bullet) { bullets.push_back(bullet); }

void Map::add_item(Item* item) { items.push_back(item); }

void Map::set_name(const std::string& name) { map_name = name; }

DynamicMap Map::get_dynamic_map() const { return dynamic_map; }

PhysicalMap Map::get_physical_map() const { return physical_map; }

std::map<int, std::vector<SpawnPoint>> Map::get_spawn_points() const { return spawn_points; }

void Map::set_physical_map(const PhysicalMap& physical_map) { this->physical_map = physical_map; }

void Map::set_dynamic_map(const DynamicMap& dynamic_map) { this->dynamic_map = dynamic_map; }

void Map::set_spawn_points(const std::map<int, std::vector<SpawnPoint>>& spawn_points) {
    this->spawn_points = spawn_points;
}

void Map::set_amount_players(int amount_players) { this->amount_players = amount_players; }

void Map::set_max_players(int max_players) { this->max_players = max_players; }

int Map::get_max_players() { return this->max_players; }

std::shared_ptr<Snapshot> Map::get_snapshot() const {
    Snapshot snapshot({}, {}, {});
    snapshot.set_dimensions(height, width, RABBIT_HEIGHT_DEFAULT, RABBIT_WIDTH_DEFAULT,
                            amount_players);
    return std::make_shared<Snapshot>(snapshot);
}

std::vector<RabbitSnapshot> Map::get_rabbit_snapshot() {
    /*
    std::vector<RabbitSnapshot> rabbit_snapshots;
    for (auto player: players) {
        RabbitSnapshot rabbit_snapshot(player->get_id(), player->get_x(), player->get_y(),
                                       player->get_health(), player->get_max_health,
    player->get_direction(), player->get_weapon(), player->get_state(), player->get_current_ammo());
        rabbit_snapshots.push_back(rabbit_snapshot);
    }
    return rabbit_snapshots;
    */
}

std::vector<ProjectileSnapshot> Map::get_projectile_snapshot() {
    /*
    std::vector<ProjectileSnapshot> projectile_snapshots;
    for (auto bullet: bullets) {
        ProjectileSnapshot projectile_snapshot(bullet->get_id(), bullet->get_x(), bullet->get_y(),
                                               bullet->get_angle(), bullet->get_speed(),
    bullet->get_damage()); projectile_snapshots.push_back(projectile_snapshot);
    }
    return projectile_snapshots;
    */
}

std::vector<SupplySnapshot> Map::get_supply_snapshot() {
    /*
    std::vector<SupplySnapshot> supply_snapshots;
    for (auto item: items) {
        SupplySnapshot supply_snapshot(item->get_id(), item->get_x(), item->get_y());
        supply_snapshots.push_back(supply_snapshot);
    }
    return supply_snapshots;
    */
}


void Map::create_entities() {
    for (int i = 0; i < amount_players; i++) {
        players.push_back(new Rabbit(spawn_points[RABBIT_SPAWN].at(i).get_x(),
                                     spawn_points[RABBIT_SPAWN].at(i).get_y(), physical_map,
                                     *this));
    }
    for (int i = 0; i < spawn_points[CRAB_SPAWN].size(); i++) {
        enemies.push_back(new Enemy(spawn_points[CRAB_SPAWN].at(i).get_x(),
                                    spawn_points[CRAB_SPAWN].at(i).get_y(), physical_map));
    }
    for (int i = 0; i < spawn_points[LIZARD_SPAWN].size(); i++) {
        enemies.push_back(new Enemy(spawn_points[LIZARD_SPAWN].at(i).get_x(),
                                    spawn_points[LIZARD_SPAWN].at(i).get_y(), physical_map));
    }
    for (int i = 0; i < spawn_points[TURTLE_SPAWN].size(); i++) {
        enemies.push_back(new Enemy(spawn_points[TURTLE_SPAWN].at(i).get_x(),
                                    spawn_points[TURTLE_SPAWN].at(i).get_y(), physical_map));
    }
    for (int i = 0; i < spawn_points[COIN_SPAWN].size(); i++) {
        items.push_back(new Item(spawn_points[COIN_SPAWN].at(i).get_x(),
                                 spawn_points[COIN_SPAWN].at(i).get_y()));
    }
    for (int i = 0; i < spawn_points[GEM_SPAWN].size(); i++) {
        items.push_back(new Item(spawn_points[GEM_SPAWN].at(i).get_x(),
                                 spawn_points[GEM_SPAWN].at(i).get_y()));
    }
}

std::string Map::get_name() const { return map_name; }

Map::~Map() {}
