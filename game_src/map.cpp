#include "map.h"

Map::Map(int width, int height, int amount_players, const std::string& map_name):
        map_name(map_name),
        width(width),
        height(height),
        amount_players(amount_players),
        max_players(0) {}


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
    for (auto& player: players) {
        if (player->get_rabbit_id() == NULL_ID) {
            player->set_rabbit_id(PlayerID);
            player->set_champion(champion);
            return;
        }
    }
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
    std::cout << "Spawn points inicializados. Cantidad de puntos para RABBIT_SPAWN: "
              << spawn_points.at(RABBIT_SPAWN).size() << std::endl;
}

void Map::set_amount_players(int amount_players) { this->amount_players = amount_players; }

void Map::set_max_players(int max_players) { this->max_players = max_players; }

int Map::get_max_players() { return this->max_players; }

int Map::get_amount_players() { return this->amount_players; }

Snapshot Map::get_snapshot() {
    // obtengo las snapshots de cada entidad
    std::vector<RabbitSnapshot> rabbit_snapshots = get_rabbit_snapshot();
    std::vector<ProjectileSnapshot> projectile_snapshots = get_projectile_snapshot();
    std::vector<SupplySnapshot> supply_snapshots = get_supply_snapshot();
    std::vector<EnemySnapshot> enemy_snapshots = get_enemy_snapshot();
    // creo el snapshot
    Snapshot snapshot(rabbit_snapshots, enemy_snapshots, projectile_snapshots, supply_snapshots);
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
                            RABBIT_AMOUNT_DEFAULT, dynamic_map);
    return snapshot;
}

std::vector<RabbitSnapshot> Map::get_rabbit_snapshot() {
    std::vector<RabbitSnapshot> rabbit_snapshots;
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
        players.push_back(new Rabbit(NULL_CHAMPION_TYPE, spawn_points[RABBIT_SPAWN].at(i).get_x() * BLOCK_DIVISION,
                                     spawn_points[RABBIT_SPAWN].at(i).get_y() * BLOCK_DIVISION, physical_map,
                                     *this));
    }
    for (int i = 0; i < spawn_points[CRAB_SPAWN].size(); i++) {
        enemies.push_back(new Enemy(id_counter_enemy, CRAB, spawn_points[CRAB_SPAWN].at(i).get_x()* BLOCK_DIVISION,
                                    spawn_points[CRAB_SPAWN].at(i).get_y()* BLOCK_DIVISION, physical_map));
        id_counter_enemy++;
    }
    for (int i = 0; i < spawn_points[LIZARD_SPAWN].size(); i++) {
        enemies.push_back(new Enemy(id_counter_enemy, LIZARD,
                                    spawn_points[LIZARD_SPAWN].at(i).get_x()* BLOCK_DIVISION,
                                    spawn_points[LIZARD_SPAWN].at(i).get_y()* BLOCK_DIVISION, physical_map));
        id_counter_enemy++;
    }
    for (int i = 0; i < spawn_points[TURTLE_SPAWN].size(); i++) {
        enemies.push_back(new Enemy(id_counter_enemy, TURTLE,
                                    spawn_points[TURTLE_SPAWN].at(i).get_x()* BLOCK_DIVISION,
                                    spawn_points[TURTLE_SPAWN].at(i).get_y()* BLOCK_DIVISION, physical_map));
        id_counter_enemy++;
    }
    for (int i = 0; i < spawn_points[COIN_SPAWN].size(); i++) {
        items.push_back(new Coin(id_counter_supply, spawn_points[COIN_SPAWN].at(i).get_x()* BLOCK_DIVISION,
                                 spawn_points[COIN_SPAWN].at(i).get_y()* BLOCK_DIVISION));
        id_counter_supply++;
    }
    for (int i = 0; i < spawn_points[GEM_SPAWN].size(); i++) {
        items.push_back(new Gem(id_counter_supply, spawn_points[GEM_SPAWN].at(i).get_x()* BLOCK_DIVISION,
                                spawn_points[GEM_SPAWN].at(i).get_y()* BLOCK_DIVISION));
        id_counter_supply++;
    }
}

std::string Map::get_name() const { return map_name; }

int Map::get_rabbit_position_by_id(int id) {
    for (int i = 0; i < players.size(); i++) {
        if (players[i]->get_rabbit_id() == id) {
            return i;
        }
    }
    return -1;
}

void Map::execute_jump(int playerID) {
    int player_pos = get_rabbit_position_by_id(playerID);
    if (player_pos != -1) {
        players[player_pos]->jump();
    }
}

void Map::execute_move(int playerID, int dir) {
    int player_pos = get_rabbit_position_by_id(playerID);
    std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWplayer_pos: " << player_pos << std::endl;
    if (player_pos != -1) {
        std::cout << "XXXXXXXXXXXXXX: " << player_pos << std::endl;
        if (dir == LEFT) {
            std::cout << "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGg: " << player_pos << std::endl;
            players[player_pos]->run_left();
        } else {
            std::cout << "LLLLLLLLLLLLLLLLLLLLL: " << player_pos << std::endl;
            players[player_pos]->run_right();
        }
    }
}

void Map::execute_move_faster(int playerID, int dir) {
    int player_pos = get_rabbit_position_by_id(playerID);
    if (player_pos != -1) {
        if (dir == LEFT) {
            players[player_pos]->run_fast_left();
        } else {
            players[player_pos]->run_fast_right();
        }
    }
}

void Map::execute_change_weapon(int playerID) {
    int player_pos = get_rabbit_position_by_id(playerID);
    if (player_pos != -1) {
        players[player_pos]->change_weapon();
    }
}

void Map::execute_shoot(int playerID) {
    int player_pos = get_rabbit_position_by_id(playerID);
    if (player_pos != -1) {
        players[player_pos]->shoot();
    }
}

Map::~Map() {}
