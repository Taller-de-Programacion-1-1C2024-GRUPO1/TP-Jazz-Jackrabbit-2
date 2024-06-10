#include "rabbit.h"

#include "../../server_src/config.h"
#include "../commands/command.h"
#include "../map.h"

#include "bullet.h"
#include "enemy.h"
#include "gun.h"
#include "item.h"
#include "state.h"

#define PLAYER_INITIAL_HEALTH ConfigSingleton::getInstance().getPlayerStartingLife()
#define POINTS_KILLING_RABBIT ConfigSingleton::getInstance().getKillRabbitPoints()
#define PLAYER_SPEED ConfigSingleton::getInstance().getRabbitSpeed()
#define JUMPING_INITIAL_SPEED ConfigSingleton::getInstance().getRabbitJumpSpeed()

Rabbit::Rabbit(uint8_t champion_type, int init_pos_x, int init_pos_y, PhysicalMap& physical_map,
               Map& map):
        Character(PLAYER_SIDE, PLAYER_SIDE, init_pos_x, init_pos_y, physical_map,
                  PLAYER_INITIAL_HEALTH),
        id(NULL_ID),
        champion_type(champion_type),
        spawn_x(init_pos_x),
        spawn_y(init_pos_y),
        action(STAND),
        direction(LEFT),
        map(map),
        points(0),
        current_gun(0) {
    state = new Alive(*this);
    gun_inventory.push_back(new BasicGun(*this, this->map));
    gun_inventory.push_back(new MachineGun(*this, this->map));
    gun_inventory.push_back(new Sniper(*this, this->map));
}


////////////////////////////////////////////////////////
void Rabbit::set_rabbit_id(int id) {
    this->id = id;
}
////////////////////////////////////////////////////////////

void Rabbit::add_machinegun_ammo(int amount_ammo) {
    gun_inventory[MACHINE_GUN]->add_ammo(amount_ammo);
}
void Rabbit::add_sniper_ammo(int amount_ammo) { gun_inventory[SNIPER]->add_ammo(amount_ammo); }

void Rabbit::revive() {
    health = PLAYER_INITIAL_HEALTH;
    gun_inventory[MACHINE_GUN]->reset_ammo_amount();
    gun_inventory[SNIPER]->reset_ammo_amount();
    current_gun = BASIC_GUN;
    pos_x = spawn_x;
    pos_y = spawn_y;
    set_state(new Alive(*this));
}

void Rabbit::set_champion(uint8_t champion_type) { this->champion_type = champion_type; }

void Rabbit::set_action_shoot() { action = SHOOT; }

int Rabbit::get_rabbit_id() { return id; }

void Rabbit::receive_damage(int damage) {
    if (state->can_receive_damage()) {
        health -= damage;
        if (health <= 0) {
            set_state(new Dead(*this));
        } else {
            set_state(new RecievedDamage(*this));
        }
    }
}

void Rabbit::add_points(int amount_of_points) {
    points += amount_of_points;
    printf("Points: %d\n", points);
}

void Rabbit::on_colision_with(PhysicalObject* object) { object->on_colision_with_rabbit(this); }


bool Rabbit::is_killed_by_taking_damage(int damage) {
    bool killed = false;
    if (state->can_receive_damage()) {
        health -= damage;
        if (health <= 0) {
            set_state(new Dead(*this));
            killed = true;
        } else {
            set_state(new RecievedDamage(*this));
        }
    }
    printf("Healtfawefwegfwergergwerfh: %d, damage %d\n", health, damage);
    return killed;
}


void Rabbit::hit_by_bullet(Bullet* bullet, int damage) {
    if (is_killed_by_taking_damage(damage)) {
        bullet->bullet_killed_target(POINTS_KILLING_RABBIT);
    }
}

void Rabbit::update() {
    action = STAND;
    state->update();
    update_guns();
    handle_events();
    Character::update_position();

    update_action();


    // NO HAY INERCIA EN EJE X
    spe_x = 0;

    /*
    printf(action == STAND          ? "STAND\n" :
           action == RUN            ? "RUN\n" :
           action == RUN_FAST       ? "RUN_FAST\n" :
           action == JUMPING        ? "JUMPING\n" :
           action == FALLING        ? "FALLING\n" :
           action == SHOOT          ? "SHOOT\n" :
           action == SPECIAL_ATTACK ? "SPECIAL_ATTACK\n" :
                                      "DIE\n");
    */
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
// SPECIAL ATTACK
void Rabbit::execute_special_attack() { action = SPECIAL_ATTACK; }

// CHANGE_WEAPON
void Rabbit::execute_change_weapon() {
    std::cout << "Cambiando arma" << std::endl;
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
void Rabbit::special_attack() { state->special_attack(); }
void Rabbit::change_weapon() { state->change_weapon(); }


// COLA
void Rabbit::add_command(std::shared_ptr<Command> command) { events_queue.push(command); }

void Rabbit::set_state(State* new_state) {
    delete state;
    state = new_state;
}

RabbitSnapshot Rabbit::get_snapshot() {
    return RabbitSnapshot(id, direction, champion_type, pos_x, pos_y, points, health, current_gun,
                          gun_inventory[current_gun]->get_ammo(), state->get_type(), action);
}

Rabbit::~Rabbit() {
    delete state;
    for (int i = 0; i < gun_inventory.size(); i++) {
        delete gun_inventory[i];
    }
}
