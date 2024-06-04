#ifndef STATE_H
#define STATE_H
#include "rabbit.h"


#define RABBIT_REVIVAL_TIME 5
#define RABBIT_DEINTOXICATE_TIME 0.5
#define RABBIT_COOLDOWN_TAKE_DAMAGE 3

class State {
protected:
    Rabbit& rabbit;
public:
    State(Rabbit& rabbit): rabbit(rabbit) {}

    virtual void update() = 0;

    virtual void jump() = 0;
    virtual void run_right() = 0;
    virtual void run_fast_right() = 0;
    virtual void run_left() = 0;
    virtual void run_fast_left() = 0;
    virtual void shoot() = 0;
    virtual void special_attack() = 0;

    virtual bool can_receive_damage() = 0;
};

class Alive: public State {
public:
    Alive(Rabbit& rabbit): State(rabbit) {}
    void update(){};

    void jump(){rabbit.execute_jump();};
    void run_right(){rabbit.execute_run_right();};
    void run_fast_right(){rabbit.execute_run_fast_right();};
    void run_left(){rabbit.execute_run_left();};
    void run_fast_left(){rabbit.execute_run_fast_left();};
    void shoot(){rabbit.execute_shoot();};
    void special_attack(){rabbit.execute_special_attack();};

    bool can_receive_damage() {return true;}    
};

class Dead: public State {
private:
    int time_to_revive;
public:
    Dead(Rabbit& rabbit): State(rabbit),time_to_revive(0) {}
    void update(){
        time_to_revive++;
        printf("DEAD\n");
        //printf("Time to revive: %d\n", time_to_revive);
        if (time_to_revive >= (RABBIT_REVIVAL_TIME * 60/*CAMBIAR POR FPS*/)) {
            rabbit.set_state(new Alive(rabbit));
        }
    };
    void jump(){};
    void run_right(){};
    void run_fast_right(){};
    void run_left(){};
    void run_fast_left(){};
    void shoot(){};
    void special_attack(){};

    bool can_receive_damage() {return false;}
};

class RecievedDamage: public State {
private:
    int cooldown_take_damage;
public:
    RecievedDamage(Rabbit& rabbit): State(rabbit), cooldown_take_damage(0) {}
    void update(){
        cooldown_take_damage++;
        printf("Time to DeDamage: %d\n", cooldown_take_damage);
        if (cooldown_take_damage >= (RABBIT_DEINTOXICATE_TIME * 60/*CAMBIAR POR FPS*/)) {
            rabbit.set_state(new Alive(rabbit));
        }
    };
    void jump(){rabbit.execute_jump();};
    void run_right(){rabbit.execute_run_right();};
    void run_fast_right(){rabbit.execute_run_fast_right();};
    void run_left(){rabbit.execute_run_left();};
    void run_fast_left(){rabbit.execute_run_fast_left();};
    void shoot(){};
    void special_attack(){};

    bool can_receive_damage() {return false;}
};

class Intoxicated: public State {
private:
    int time_to_deintoxicate;
public:
    Intoxicated(Rabbit& rabbit): State(rabbit), time_to_deintoxicate(0) {}
    void update(){
        time_to_deintoxicate++;
        printf("Time to revive: %d\n", time_to_deintoxicate);
        if (time_to_deintoxicate >= (RABBIT_DEINTOXICATE_TIME * 60/*CAMBIAR POR FPS*/)) {
            rabbit.set_state(new Alive(rabbit));
        }
    };
    void jump(){rabbit.execute_jump();};
    void run_right(){rabbit.execute_run_right();};
    void run_fast_right(){rabbit.execute_run_fast_right();};
    void run_left(){rabbit.execute_run_left();};
    void run_fast_left(){rabbit.execute_run_fast_left();};
    void shoot(){};
    void special_attack(){};

    bool can_receive_damage() {return true;}
};

#endif