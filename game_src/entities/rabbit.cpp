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

Rabbit::Rabbit(uint8_t champion_type, int init_pos_x, int init_pos_y, PhysicalMap& map,
               Map& manager):
        Character(PLAYER_SIDE, PLAYER_SIDE, init_pos_x, init_pos_y, map, PLAYER_INITIAL_HEALTH),
        id(NULL_ID),
        champion_type(champion_type),
        spawn_x(init_pos_x),
        spawn_y(init_pos_y),
        action(STAND),
        acc_y(GRAVITY),
        direction(LEFT),
        manager(manager),
        points(0),
        current_gun(0) {
    state = new Alive(*this);
    gun_inventory.push_back(new BasicGun(*this, manager));
    gun_inventory.push_back(new MachineGun(*this, manager));
    gun_inventory.push_back(new Sniper(*this, manager));
}

void Rabbit::set_rabbit_id(int id) { this->id = id; }

void Rabbit::set_champion(uint8_t champion_type) { this->champion_type = champion_type; }

void Rabbit::set_action_shoot(){
    action = SHOOT;
}

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
    update_position();

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


void Rabbit::update_position() {
    // GRAVITY
    if (!on_floor && spe_y < MAX_FALLING_SPEED) {
        spe_y += acc_y;
    }
    // ACTUALIZA POSICIONES
    pos_x += spe_x;
    pos_y += spe_y;

    // REPOSITION
    check_colision_with_map();
    if (on_floor) {
        if (!on_left_slope && !on_right_slope) {
            pos_y = pos_y - ((pos_y % BLOCK_DIVISION) +1);
        }
        spe_y = 0;
    }
    if (on_roof) {
        pos_y = pos_y + (BLOCK_DIVISION - (pos_y % BLOCK_DIVISION));
        spe_y = 0;
    }
    if (on_left_wall) {
        pos_x = pos_x + (BLOCK_DIVISION - (pos_x % BLOCK_DIVISION));
    }
    if (on_right_wall) {
        pos_x = pos_x - (pos_x % BLOCK_DIVISION);
    }

    check_colision_with_map();
    if (on_right_slope) {

       pos_y += BLOCK_DIVISION-(pos_x % BLOCK_DIVISION)-(pos_y % BLOCK_DIVISION);
    } else if (on_left_slope) {

       pos_y += (pos_x % BLOCK_DIVISION)-(pos_y % BLOCK_DIVISION);
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

    if (action!=SHOOT){
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
    if (map.can_jump(pos_x, pos_y, width, height)) {
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


void Rabbit::jump() { state->jump(); }
void Rabbit::run_right() { state->run_right(); }
void Rabbit::run_fast_right() { state->run_fast_right(); }
void Rabbit::run_left() { state->run_left(); }
void Rabbit::run_fast_left() { state->run_fast_left(); }
void Rabbit::shoot() { state->shoot(); }
void Rabbit::special_attack() { state->special_attack(); }

void Rabbit::change_weapon() {}

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

Rabbit::~Rabbit() { delete state; }
