#ifndef STATE_H
#define STATE_H

#include "../../server_src/config.h"
#include "../constants_game.h"

#include "rabbit.h"

#define RABBIT_REVIVAL_TIME ConfigSingleton::getInstance().getRabbitRevivalTime()
#define RABBIT_DEINTOXICATE_TIME ConfigSingleton::getInstance().getRabbitDeintoxicateTime()

class State {
protected:
    Rabbit& rabbit;
    int type;
    int change_weapon_cooldown;

public:
    State(int type, Rabbit& rabbit): type(type), rabbit(rabbit), change_weapon_cooldown(0) {}

    int get_type() { return type; }

    virtual void update() = 0;

    virtual void jump() = 0;
    virtual void run_right() = 0;
    virtual void run_fast_right() = 0;
    virtual void run_left() = 0;
    virtual void run_fast_left() = 0;
    virtual void shoot() = 0;
    virtual void special_attack() = 0;
    virtual void change_weapon() = 0;

    virtual bool can_receive_damage() = 0;

    virtual ~State() = default;
};

class Alive: public State {
public:
    explicit Alive(Rabbit& rabbit): State(ALIVE, rabbit) {}

    void update() override {
        if (change_weapon_cooldown > 0) {
            change_weapon_cooldown--;
        }
    }
    void jump() override { rabbit.execute_jump(); }
    void run_right() override { rabbit.execute_run_right(); }
    void run_fast_right() override { rabbit.execute_run_fast_right(); }
    void run_left() override { rabbit.execute_run_left(); }
    void run_fast_left() override { rabbit.execute_run_fast_left(); }
    void shoot() override { rabbit.execute_shoot(); }
    void special_attack() override { rabbit.execute_special_attack(); }
    bool can_receive_damage() override { return true; }
    void change_weapon() override {
        if (change_weapon_cooldown == 0) {
            rabbit.execute_change_weapon();
            change_weapon_cooldown = CHANGE_WEAPON_COOLDOWN;
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
        printf("DEAD\n");
        // printf("Time to revive: %d\n", time_to_revive);
        if (time_to_revive >= (RABBIT_REVIVAL_TIME * 60 /*CAMBIAR POR FPS*/)) {
            rabbit.revive();
        }
    }
    void jump() override {}
    void run_right() override {}
    void run_fast_right() override {}
    void run_left() override {}
    void run_fast_left() override {}
    void shoot() override {}
    void special_attack() override {}
    void change_weapon() override {}

    bool can_receive_damage() override { return false; }
};

class RecievedDamage: public State {
private:
    int cooldown_take_damage;

public:
    explicit RecievedDamage(Rabbit& rabbit):
            State(RECIEVED_DAMAGE, rabbit), cooldown_take_damage(0) {}

    void update() override {
        cooldown_take_damage++;
        printf("Time to DeDamage: %d\n", cooldown_take_damage);
        if (cooldown_take_damage >= (RABBIT_DEINTOXICATE_TIME * 60 /*CAMBIAR POR FPS*/)) {
            rabbit.set_state(new Alive(rabbit));
        }
        if (change_weapon_cooldown > 0) {
            change_weapon_cooldown--;
        }
    }
    void jump() override { rabbit.execute_jump(); }
    void run_right() override { rabbit.execute_run_right(); }
    void run_fast_right() override { rabbit.execute_run_fast_right(); }
    void run_left() override { rabbit.execute_run_left(); }
    void run_fast_left() override { rabbit.execute_run_fast_left(); }
    void shoot() override {}
    void special_attack() override {}
    void change_weapon() override {
        if (change_weapon_cooldown == 0) {
            rabbit.execute_change_weapon();
            change_weapon_cooldown = CHANGE_WEAPON_COOLDOWN;
        }
    }

    bool can_receive_damage() override { return false; }
};

class Intoxicated: public State {
private:
    int time_to_deintoxicate;

public:
    explicit Intoxicated(Rabbit& rabbit): State(INTOXICATED, rabbit), time_to_deintoxicate(0) {}

    void update() override {
        time_to_deintoxicate++;
        printf("Time to revive: %d\n", time_to_deintoxicate);
        if (time_to_deintoxicate >= (RABBIT_DEINTOXICATE_TIME * 60 /*CAMBIAR POR FPS*/)) {
            rabbit.set_state(new Alive(rabbit));
        }
        if (change_weapon_cooldown > 0) {
            change_weapon_cooldown--;
        }
    }
    void jump() override { rabbit.execute_jump(); }
    void run_right() override { rabbit.execute_run_right(); }
    void run_fast_right() override { rabbit.execute_run_fast_right(); }
    void run_left() override { rabbit.execute_run_left(); }
    void run_fast_left() override { rabbit.execute_run_fast_left(); }
    void shoot() override {}
    void special_attack() override {}
    void change_weapon() override {
        if (change_weapon_cooldown == 0) {
            rabbit.execute_change_weapon();
            change_weapon_cooldown = CHANGE_WEAPON_COOLDOWN;
        }
    }
    bool can_receive_damage() override { return true; }
};

#endif
