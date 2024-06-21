#ifndef STATE_H
#define STATE_H

#include "../constants_game.h"

#include "rabbit.h"


class State {
protected:
    Rabbit& rabbit;
    int type;
    int change_weapon_cooldown;
    int change_status_cooldown;

public:
    State(int type, Rabbit& rabbit):
            type(type), rabbit(rabbit), change_weapon_cooldown(0), change_status_cooldown(20) {}

    int get_type() { return type; }

    virtual void update() = 0;

    virtual void jump() = 0;
    virtual void run_right() = 0;
    virtual void run_fast_right() = 0;
    virtual void run_left() = 0;
    virtual void run_fast_left() = 0;
    virtual void shoot() = 0;
    virtual void change_weapon() = 0;

    virtual bool can_do_special_attack() = 0;
    virtual bool can_receive_damage() = 0;
    virtual bool does_damage() = 0;

    virtual void execute_godmode() = 0;

    virtual ~State() = default;
};

class Alive: public State {
public:
    explicit Alive(Rabbit& rabbit): State(ALIVE, rabbit) {}

    void update() override {
        if (change_weapon_cooldown > 0) {
            change_weapon_cooldown--;
        }
        if (change_status_cooldown > 0) {
            change_status_cooldown--;
        }
    }
    void jump() override { rabbit.execute_jump(); }
    void run_right() override { rabbit.execute_run_right(); }
    void run_fast_right() override { rabbit.execute_run_fast_right(); }
    void run_left() override { rabbit.execute_run_left(); }
    void run_fast_left() override { rabbit.execute_run_fast_left(); }
    void shoot() override { rabbit.execute_shoot(); }
    bool can_receive_damage() override { return true; }
    void change_weapon() override {
        if (change_weapon_cooldown == 0) {
            rabbit.execute_change_weapon();
            change_weapon_cooldown = CHANGE_WEAPON_COOLDOWN;
        }
    }
    bool can_do_special_attack() override { return true; }
    bool does_damage() override { return false; }
    void execute_godmode() override {
        if (change_status_cooldown == 0) {
            rabbit.set_godmode();
        }
    }
};

class Dead: public State {
private:
    int time_to_revive;

public:
    explicit Dead(Rabbit& rabbit): State(DEAD, rabbit), time_to_revive(0) {}

    void update() override {
        time_to_revive++;
        if (change_status_cooldown > 0) {
            change_status_cooldown--;
        }
        if (time_to_revive >= (RABBIT_REVIVAL_TIME * UPDATE_RATE)) {
            rabbit.revive();
        }
    }
    void jump() override {}
    void run_right() override {}
    void run_fast_right() override {}
    void run_left() override {}
    void run_fast_left() override {}
    void shoot() override {}
    void change_weapon() override {}

    bool can_do_special_attack() override { return false; }
    bool can_receive_damage() override { return false; }
    bool does_damage() override { return false; }
    void execute_godmode() override {
        if (change_status_cooldown == 0) {
            rabbit.set_godmode();
        }
    }
};

class RecievedDamage: public State {
private:
    int cooldown_take_damage;

public:
    explicit RecievedDamage(Rabbit& rabbit):
            State(RECIEVED_DAMAGE, rabbit), cooldown_take_damage(0) {}

    void update() override {
        cooldown_take_damage++;
        if (change_weapon_cooldown > 0) {
            change_weapon_cooldown--;
        }
        if (change_status_cooldown > 0) {
            change_status_cooldown--;
        }
        if (cooldown_take_damage >= (UPDATE_RATE)) {
            rabbit.set_alive();
        }
    }
    void jump() override { rabbit.execute_jump(); }
    void run_right() override { rabbit.execute_run_right(); }
    void run_fast_right() override { rabbit.execute_run_fast_right(); }
    void run_left() override { rabbit.execute_run_left(); }
    void run_fast_left() override { rabbit.execute_run_fast_left(); }
    void shoot() override {}
    void change_weapon() override {
        if (change_weapon_cooldown == 0) {
            rabbit.execute_change_weapon();
            change_weapon_cooldown = CHANGE_WEAPON_COOLDOWN;
        }
    }
    bool can_do_special_attack() override { return false; }
    bool can_receive_damage() override { return false; }
    bool does_damage() override { return false; }
    void execute_godmode() override {
        if (change_status_cooldown == 0) {
            rabbit.set_godmode();
        }
    }
};

class Intoxicated: public State {
private:
    int time_to_deintoxicate;

public:
    explicit Intoxicated(Rabbit& rabbit): State(INTOXICATED, rabbit), time_to_deintoxicate(0) {}

    void update() override {
        time_to_deintoxicate++;
        if (change_weapon_cooldown > 0) {
            change_weapon_cooldown--;
        }
        if (change_status_cooldown > 0) {
            change_status_cooldown--;
        }
        if (time_to_deintoxicate >= (RABBIT_DEINTOXICATE_TIME * UPDATE_RATE)) {
            rabbit.set_alive();
        }
    }
    void jump() override { rabbit.execute_jump(); }
    void run_right() override { rabbit.execute_run_right(); }
    void run_fast_right() override { rabbit.execute_run_fast_right(); }
    void run_left() override { rabbit.execute_run_left(); }
    void run_fast_left() override { rabbit.execute_run_fast_left(); }
    void shoot() override {}
    void change_weapon() override {
        if (change_weapon_cooldown == 0) {
            rabbit.execute_change_weapon();
            change_weapon_cooldown = CHANGE_WEAPON_COOLDOWN;
        }
    }
    bool can_do_special_attack() override { return false; }
    bool can_receive_damage() override { return true; }
    bool does_damage() override { return false; }
    void execute_godmode() override {
        if (change_status_cooldown == 0) {
            rabbit.set_godmode();
        }
    }
};


class SpecialAttackJazzState: public State {
private:
    int time_to_finish;

public:
    explicit SpecialAttackJazzState(Rabbit& rabbit):
            State(SPECIAL_ATTACK_JAZZ, rabbit), time_to_finish(0) {}
    void update() override {
        time_to_finish++;
        if (time_to_finish >= (SPECIAL_ATTACK_TIME)) {
            rabbit.set_alive();
        }
    }
    void jump() override {}
    void run_right() override {}
    void run_fast_right() override {}
    void run_left() override {}
    void run_fast_left() override {}
    void shoot() override {}
    bool can_do_special_attack() override { return false; }
    void change_weapon() override {}

    bool can_receive_damage() override { return false; }
    bool does_damage() override { return true; }
    void execute_godmode() override {}
};
class SpecialAttackSpazState: public State {
private:
    int direction;
    int time_to_finish;

public:
    SpecialAttackSpazState(Rabbit& rabbit, int direction):
            State(SPECIAL_ATTACK_SPAZ, rabbit), direction(direction), time_to_finish(0) {}
    void update() override {
        if (direction == RIGHT) {
            rabbit.execute_run_fast_right();
        } else {
            rabbit.execute_run_fast_left();
        }
        time_to_finish++;
        if (time_to_finish >= (SPECIAL_ATTACK_TIME)) {
            rabbit.set_alive();
        }
    }
    void jump() override {}
    void run_right() override {}
    void run_fast_right() override {}
    void run_left() override {}
    void run_fast_left() override {}
    void shoot() override {}
    bool can_do_special_attack() override { return false; }
    void change_weapon() override {}

    bool can_receive_damage() override { return false; }
    bool does_damage() override { return true; }
    void execute_godmode() override {}
};

class SpecialAttackLoriState: public State {
private:
    int time_to_finish;

public:
    explicit SpecialAttackLoriState(Rabbit& rabbit):
            State(SPECIAL_ATTACK_LORI, rabbit), time_to_finish(0) {}
    void update() override {
        time_to_finish++;
        if (time_to_finish >= (SPECIAL_ATTACK_TIME)) {
            rabbit.set_alive();
        }
    }
    void jump() override {}
    void run_right() override { rabbit.execute_run_right(); }
    void run_fast_right() override { rabbit.execute_run_right(); }
    void run_left() override { rabbit.execute_run_left(); }
    void run_fast_left() override { rabbit.execute_run_left(); }
    void shoot() override {}
    bool can_do_special_attack() override { return false; }
    void change_weapon() override {}

    bool can_receive_damage() override { return false; }
    bool does_damage() override { return true; }
    void execute_godmode() override {}
};

class GodMode: public State {
public:
    explicit GodMode(Rabbit& rabbit): State(ALIVE, rabbit) {}

    void update() override {
        if (change_weapon_cooldown > 0) {
            change_weapon_cooldown--;
        }
        if (change_status_cooldown > 0) {
            change_status_cooldown--;
        }
    }
    void jump() override { rabbit.execute_jump(); }
    void run_right() override { rabbit.execute_run_right(); }
    void run_fast_right() override { rabbit.execute_run_fast_right(); }
    void run_left() override { rabbit.execute_run_left(); }
    void run_fast_left() override { rabbit.execute_run_fast_left(); }
    void shoot() override { rabbit.execute_shoot(); }
    bool can_receive_damage() override { return false; }
    void change_weapon() override {
        if (change_weapon_cooldown == 0) {
            rabbit.execute_change_weapon();
            change_weapon_cooldown = CHANGE_WEAPON_COOLDOWN;
        }
    }
    bool can_do_special_attack() override { return true; }
    bool does_damage() override { return false; }
    void execute_godmode() override {
        if (change_status_cooldown == 0) {
            rabbit.set_alive();
        }
    }
};

#endif
