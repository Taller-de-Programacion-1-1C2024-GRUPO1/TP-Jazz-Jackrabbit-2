#include "rabbit.h"

#include "../commands/command.h"
#include "../map.h"

#include "bullet.h"
#include "enemy.h"
#include "gun.h"
#include "item.h"
#include "state.h"


Rabbit::Rabbit(uint8_t champion_type, int init_pos_x, int init_pos_y, PhysicalMap& physical_map,
               Map& map):
        Character(PLAYER_SIDE, PLAYER_SIDE, init_pos_x, init_pos_y, physical_map,
                  PLAYER_INITIAL_HEALTH),
        id(NULL_ID),
        champion_type(champion_type),
        max_health(PLAYER_INITIAL_HEALTH),
        spawn_x(init_pos_x),
        spawn_y(init_pos_y),
        action(STAND),
        direction(LEFT),
        map(map),
        points(0),
        current_gun(0),
        state_needs_change(false),
        state(new Alive(*this)),
        player_name("") {
    gun_inventory.push_back(new BasicGun(*this, this->map));
    gun_inventory.push_back(new FlameThrower(*this, this->map));
    gun_inventory.push_back(new RocketLauncher(*this, this->map));
    gun_inventory.push_back(new RayGun(*this, this->map));
}

void Rabbit::set_rabbit_info(int id_received, uint8_t champion_type_received,
                             const std::string& player_name_received) {
    this->id = id_received;
    this->champion_type = champion_type_received;
    this->player_name = player_name_received;
}

void Rabbit::colided_with_enemy(Enemy* enemy, int damage) {
    receive_damage(damage);
    if (state->does_damage()) {
        (enemy->hit_by_rabbit_specialattack(this, PLAYER_DAMAGE));
    }
}

void Rabbit::on_colision_with_rabbit(Rabbit* rabbit_2) {
    if (state->does_damage()) {
        if (rabbit_2->is_killed_by_taking_damage(PLAYER_DAMAGE)) {
            add_points(POINTS_KILLING_RABBIT);
        }
    }
}

void Rabbit::add_health(int amount_health) {
    health += amount_health;
    if (health > max_health) {
        health = max_health;
    }
}

void Rabbit::add_machinegun_ammo(int amount_ammo) {
    gun_inventory[FLAMETHROWER]->add_ammo(amount_ammo);
}
void Rabbit::add_sniper_ammo(int amount_ammo) {
    gun_inventory[ROCKETLAUNCHER]->add_ammo(amount_ammo);
}

void Rabbit::add_raygun_ammo(int amount_ammo) { gun_inventory[RAYGUN]->add_ammo(amount_ammo); }

void Rabbit::receive_max_ammo() {
    for (int i = 0; i < gun_inventory.size(); i++) {
        gun_inventory[i]->execute_max_ammo();
    }
}
void Rabbit::receive_max_health() { health = max_health; }
void Rabbit::receive_god_mode() { state->execute_godmode(); }

void Rabbit::respawn() {
    pos_x = spawn_x;
    pos_y = spawn_y;
}

void Rabbit::revive() {
    health = PLAYER_INITIAL_HEALTH;
    gun_inventory[FLAMETHROWER]->reset_ammo_amount();
    gun_inventory[ROCKETLAUNCHER]->reset_ammo_amount();
    gun_inventory[RAYGUN]->reset_ammo_amount();
    current_gun = BASIC_GUN;
    set_state(ALIVE);
    respawn();
}


void Rabbit::set_action_shoot() { action = SHOOT; }

int Rabbit::get_rabbit_id() { return id; }


void Rabbit::add_points(int amount_of_points) { points += amount_of_points; }

void Rabbit::on_colision_with(PhysicalObject* object) { object->on_colision_with_rabbit(this); }


bool Rabbit::is_killed_by_taking_damage(int damage) {
    bool killed = false;
    if (state->can_receive_damage()) {
        health -= damage;
        if (health <= 0) {
            set_state(DEAD);
            killed = true;
        } else {
            set_state(RECIEVED_DAMAGE);
        }
    }
    return killed;
}


void Rabbit::hit_by_bullet(Bullet* bullet, int damage) {
    if (is_killed_by_taking_damage(damage)) {
        bullet->bullet_killed_target(POINTS_KILLING_RABBIT);
    }
}


void Rabbit::update_action() {
    // DIRECCION
    if (spe_x > 0) {
        direction = RIGHT;
    } else if (spe_x < 0) {
        direction = LEFT;
    }

    // CAMBIO DE ACCION

    if (action != SHOOT) {
        if (spe_y > 0) {
            action = FALLING;
        } else if (spe_y < 0) {
            action = JUMPING;
        } else if (spe_x == 0) {
            action = STAND;
        } else if (spe_x == PLAYER_SPEED || spe_x == -PLAYER_SPEED) {
            action = RUN;
        } else if (spe_x == PLAYER_SPEED * 2 || spe_x == -PLAYER_SPEED * 2) {
            action = RUN_FAST;
        }
    }
}

void Rabbit::update_guns() {
    for (int i = 0; i < gun_inventory.size(); i++) {
        gun_inventory[i]->update();
    }
}

void Rabbit::imprimir_posicion() { printf("X: %d Y: %d\n", pos_x, pos_y); }


// EVENTS

void Rabbit::handle_events() {
    while (!events_queue.empty()) {
        std::shared_ptr<Command> event = events_queue.front();
        events_queue.pop();
        event->execute_Command(*this);
    }
}
// JUMP
void Rabbit::execute_jump() {
    if (physical_map.can_jump(pos_x, pos_y, width, height)) {
        spe_y = -JUMPING_INITIAL_SPEED;
    }
}
// RIGHT
void Rabbit::execute_run_right() {
    check_colision_with_map();
    if (!on_right_wall) {
        spe_x = PLAYER_SPEED;
    }
}

// RIGHT SPRINT
void Rabbit::execute_run_fast_right() {
    check_colision_with_map();
    if (!on_right_wall) {
        spe_x = PLAYER_SPEED * 2;
    }
}
// LEFT
void Rabbit::execute_run_left() {
    check_colision_with_map();
    if (!on_left_wall) {
        spe_x = -PLAYER_SPEED;
    }
}
// LEFT SPRINT
void Rabbit::execute_run_fast_left() {
    check_colision_with_map();
    if (!on_left_wall) {
        spe_x = -(PLAYER_SPEED * 2);
    }
}
// SHOOT
void Rabbit::execute_shoot() {
    if (direction == LEFT) {
        gun_inventory[current_gun]->fire(pos_x, pos_y + (height / 2), direction);
    } else {
        gun_inventory[current_gun]->fire(pos_x + width, pos_y + (height / 2), direction);
    }
}


// CHANGE_WEAPON
void Rabbit::execute_change_weapon() {
    current_gun = (current_gun + 1) % gun_inventory.size();
    while (!gun_inventory[current_gun]->has_ammo()) {
        current_gun = (current_gun + 1) % gun_inventory.size();
    }
}

void Rabbit::jump() { state->jump(); }
void Rabbit::run_right() { state->run_right(); }
void Rabbit::run_fast_right() { state->run_fast_right(); }
void Rabbit::run_left() { state->run_left(); }
void Rabbit::run_fast_left() { state->run_fast_left(); }
void Rabbit::shoot() { state->shoot(); }
void Rabbit::change_weapon() { state->change_weapon(); }


// COLA
void Rabbit::add_command(std::shared_ptr<Command> command) { events_queue.push(command); }

// STATE

void Rabbit::update() {
    action = STAND;
    state->update();
    update_guns();
    handle_events();
    Character::update_position();

    update_action();
    change_state();
    // NO HAY INERCIA EN EJE X
    spe_x = 0;
}

void Rabbit::change_state() {
    if (state_needs_change) {
        delete state;
        switch (next_state) {
            case ALIVE:
                state = new Alive(*this);
                break;
            case DEAD:
                state = new Dead(*this);
                break;
            case RECIEVED_DAMAGE:
                state = new RecievedDamage(*this);
                break;
            case GODMODE_STATE:
                state = new GodMode(*this);
                break;
            case INTOXICATED:
                state = new Intoxicated(*this);
                break;
            case SPECIAL_ATTACK_JAZZ:
                state = new SpecialAttackJazzState(*this);
                break;
            case SPECIAL_ATTACK_LORI:
                state = new SpecialAttackLoriState(*this);
                break;
            case SPECIAL_ATTACK_SPAZ:
                state = new SpecialAttackSpazState(*this, direction);
                break;
        }
        state_needs_change = false;
    }
}

void Rabbit::receive_damage(int damage) {
    if (state->can_receive_damage()) {
        health -= damage;
        if (health <= 0) {
            set_state(DEAD);
        } else {
            set_state(RECIEVED_DAMAGE);
        }
    }
}

void Rabbit::set_state(int new_state) {
    state_needs_change = true;
    next_state = new_state;
}

void Rabbit::set_intoxicated() { set_state(INTOXICATED); }
void Rabbit::set_alive() { set_state(ALIVE); }
void Rabbit::set_godmode() { set_state(GODMODE_STATE); }

// ATAQUE ESPECIAL
void Rabbit::special_attack_jazz() {
    if (champion_type == Jazz && state->can_do_special_attack()) {
        execute_special_jazz();
    }
}
void Rabbit::special_attack_spaz(int direction) {
    if (champion_type == Spaz && state->can_do_special_attack()) {
        execute_special_spaz(direction);
    }
}
void Rabbit::special_attack_lori() {
    if (champion_type == Lori && state->can_do_special_attack()) {
        execute_special_lori();
    }
}

void Rabbit::execute_special_jazz() {
    // punetazo hacia arriba: Salta sin poder moverse lateralmente realizando dano
    if (physical_map.can_jump(pos_x, pos_y, width, height)) {
        execute_jump();
        set_state(SPECIAL_ATTACK_JAZZ);
    }
}
void Rabbit::execute_special_spaz(int direction) {
    // Patada hacia un costado: patada lateral sin poder saltar
    if (physical_map.can_jump(pos_x, pos_y, width, height)) {
        // Cuidado con el lado hacia donde se ejecuta el ataque
        set_state(SPECIAL_ATTACK_SPAZ);
    }
}
void Rabbit::execute_special_lori() {
    // Patada Corto Alcance: Salto generando dano
    if (physical_map.can_jump(pos_x, pos_y, width, height)) {
        execute_jump();
        set_state(SPECIAL_ATTACK_LORI);
    }
}

// SNAPSHOT
RabbitSnapshot Rabbit::get_snapshot() {
    return RabbitSnapshot(id, direction, champion_type, pos_x, pos_y, points, health, current_gun,
                          gun_inventory[current_gun]->get_ammo(), state->get_type(), action,
                          player_name);
}

// DESTRUCTOR
Rabbit::~Rabbit() {
    delete state;
    for (int i = 0; i < gun_inventory.size(); i++) {
        delete gun_inventory[i];
    }
}
