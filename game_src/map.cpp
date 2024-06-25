#include "map.h"

Map::Map(int width, int height, int texture_id, int max_players, const std::string& map_name,
         const PhysicalMap& physical_map, const DynamicMap& dynamic_map,
         const std::map<int, std::vector<SpawnPoint>>& spawn_points):
        map_name(map_name),
        physical_map(physical_map),
        dynamic_map(dynamic_map),
        spawn_points(spawn_points),
        width(width),
        height(height),
        texture_id(texture_id),
        amount_players(0),
        max_players(max_players),
        projectile_id(0) {}

int Map::get_projectile_id() { return projectile_id++; }

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
    for (auto player_A: players) {
        for (auto player_B: players) {
            if (player_A != player_B) {
                player_A->check_colision_with(player_B);
            }
        }
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

void Map::reap_dead() {
    int i = 0;
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
            delete items[i];
            items.erase(items.begin() + i);
        } else {
            i++;
        }
    }
}

void Map::add_player(int PlayerID, ChampionType champion, const std::string& player_name) {
    for (auto& player: players) {
        if (player->get_rabbit_id() == NULL_ID) {
            player->set_rabbit_info(PlayerID, champion, player_name);
            return;
        }
    }
}

void Map::add_enemy(Enemy* enemy) { enemies.push_back(enemy); }

void Map::add_bullet(Bullet* bullet) { bullets.push_back(bullet); }

void Map::add_item(Item* item) { items.push_back(item); }

DynamicMap Map::get_dynamic_map() const { return dynamic_map; }

PhysicalMap Map::get_physical_map() const { return physical_map; }

std::map<int, std::vector<SpawnPoint>> Map::get_spawn_points() const { return spawn_points; }

void Map::set_amount_players(int amount_players) { this->amount_players = amount_players; }

int Map::get_max_players() { return this->max_players; }

int Map::get_amount_players() { return this->amount_players; }

int Map::get_texture_id() { return this->texture_id; }

std::string Map::get_name() const { return map_name; }

int Map::get_width() { return width; }

int Map::get_height() { return height; }

Snapshot Map::get_snapshot(uint32_t match_time) {
    // obtengo las snapshots de cada entidad
    std::vector<RabbitSnapshot> rabbit_snapshots = get_rabbit_snapshot();
    std::vector<ProjectileSnapshot> projectile_snapshots = get_projectile_snapshot();
    std::vector<SupplySnapshot> supply_snapshots = get_supply_snapshot();
    std::vector<EnemySnapshot> enemy_snapshots = get_enemy_snapshot();
    // creo el snapshot
    Snapshot snapshot(rabbit_snapshots, enemy_snapshots, projectile_snapshots, supply_snapshots);
    snapshot.set_match_time(match_time);
    return snapshot;
}

Snapshot Map::get_init_snapshot() {
    // obtengo las snapshots de cada entidad
    std::vector<RabbitSnapshot> rabbit_snapshots = get_rabbit_snapshot();
    std::vector<ProjectileSnapshot> projectile_snapshots = get_projectile_snapshot();
    std::vector<SupplySnapshot> supply_snapshots = get_supply_snapshot();
    std::vector<EnemySnapshot> enemy_snapshots = get_enemy_snapshot();
    // creo el snapshot

    Snapshot snapshot(rabbit_snapshots, enemy_snapshots, projectile_snapshots, supply_snapshots);
    snapshot.set_dimensions(height, width, RABBIT_WIDTH_DEFAULT, RABBIT_HEIGHT_DEFAULT,
                            RABBIT_AMOUNT_DEFAULT, dynamic_map, texture_id);
    return snapshot;
}

std::vector<RabbitSnapshot> Map::get_rabbit_snapshot() {
    std::vector<RabbitSnapshot> rabbit_snapshots;
    // obtengo las snapshots de cada conejo

    for (auto player: players) {
        rabbit_snapshots.push_back(player->get_snapshot());
    }

    return rabbit_snapshots;
}

std::vector<ProjectileSnapshot> Map::get_projectile_snapshot() {
    std::vector<ProjectileSnapshot> projectile_snapshots;
    for (auto bullet: bullets) {
        projectile_snapshots.push_back(bullet->get_snapshot());
    }
    return projectile_snapshots;
}

std::vector<SupplySnapshot> Map::get_supply_snapshot() {
    std::vector<SupplySnapshot> supply_snapshots;
    for (auto item: items) {
        supply_snapshots.push_back(item->get_snapshot());
    }
    return supply_snapshots;
}

std::vector<EnemySnapshot> Map::get_enemy_snapshot() {
    std::vector<EnemySnapshot> enemy_snapshots;
    for (auto enemy: enemies) {
        enemy_snapshots.push_back(enemy->get_snapshot());
    }
    return enemy_snapshots;
}

void Map::create_entities() {
    int id_counter_enemy = 0;
    int id_counter_supply = 0;
    // VER QUE HACER CON ESTO
    if (spawn_points.at(RABBIT_SPAWN).size() < amount_players) {
        std::cerr << "map.cpp Error: No hay suficientes puntos de spawn en el mapa para los "
                     "jugadores."
                  << std::endl;
        amount_players = spawn_points[RABBIT_SPAWN].size();  // Limitar la cantidad de jugadores
    }

    for (int i = 0; i < amount_players; i++) {
        players.push_back(new Rabbit(
                NULL_CHAMPION_TYPE, spawn_points[RABBIT_SPAWN].at(i).get_x() * BLOCK_DIVISION,
                spawn_points[RABBIT_SPAWN].at(i).get_y() * BLOCK_DIVISION, physical_map, *this));
    }
    for (int i = 0; i < spawn_points[CRAB_SPAWN].size(); i++) {
        enemies.push_back(new EnemyCrab(
                id_counter_enemy, spawn_points[CRAB_SPAWN].at(i).get_x() * BLOCK_DIVISION,
                spawn_points[CRAB_SPAWN].at(i).get_y() * BLOCK_DIVISION, physical_map, *this));
        id_counter_enemy++;
    }
    for (int i = 0; i < spawn_points[LIZARD_SPAWN].size(); i++) {
        enemies.push_back(new EnemyLizard(
                id_counter_enemy, spawn_points[LIZARD_SPAWN].at(i).get_x() * BLOCK_DIVISION,
                spawn_points[LIZARD_SPAWN].at(i).get_y() * BLOCK_DIVISION, physical_map, *this));
        id_counter_enemy++;
    }
    for (int i = 0; i < spawn_points[TURTLE_SPAWN].size(); i++) {
        enemies.push_back(new EnemyTurtle(
                id_counter_enemy, spawn_points[TURTLE_SPAWN].at(i).get_x() * BLOCK_DIVISION,
                spawn_points[TURTLE_SPAWN].at(i).get_y() * BLOCK_DIVISION, physical_map, *this));
        id_counter_enemy++;
    }
    for (int i = 0; i < spawn_points[COIN_SPAWN].size(); i++) {
        items.push_back(new Coin(id_counter_supply,
                                 spawn_points[COIN_SPAWN].at(i).get_x() * BLOCK_DIVISION,
                                 spawn_points[COIN_SPAWN].at(i).get_y() * BLOCK_DIVISION));
        id_counter_supply++;
    }
    for (int i = 0; i < spawn_points[GEM_SPAWN].size(); i++) {
        items.push_back(new Gem(id_counter_supply,
                                spawn_points[GEM_SPAWN].at(i).get_x() * BLOCK_DIVISION,
                                spawn_points[GEM_SPAWN].at(i).get_y() * BLOCK_DIVISION));
        id_counter_supply++;
    }
}

int Map::get_rabbit_position_by_id(int id) {
    for (int i = 0; i < players.size(); i++) {
        if (players[i]->get_rabbit_id() == id) {
            return i;
        }
    }
    return -1;
}

void Map::add_command(std::shared_ptr<Command> command) {
    int player_pos = get_rabbit_position_by_id(command->get_playerId());
    players[player_pos]->add_command(command);
}


Map::~Map() {
    for (auto player: players) {
        delete player;
    }
    for (auto enemy: enemies) {
        delete enemy;
    }
    for (auto bullet: bullets) {
        delete bullet;
    }
    for (auto item: items) {
        delete item;
    }
}
