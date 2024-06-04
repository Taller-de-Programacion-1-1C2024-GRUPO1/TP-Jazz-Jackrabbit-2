#ifndef RABBIT_SNAPSHOT_H
#define RABBIT_SNAPSHOT_H

class RabbitSnapshot {
public:
    char id;
    int pos_x;
    int pos_y;
    int max_health;
    int health;
    char direction;
    int weapon;
    int state;
    int current_ammo;

    RabbitSnapshot(char id, int pos_x, int pos_y, int max_health, int health, char direction,
                   int weapon, int state, int current_ammo):
            id(id),
            pos_x(pos_x),
            pos_y(pos_y),
            max_health(max_health),
            health(health),
            direction(direction),
            weapon(weapon),
            state(state),
            current_ammo(current_ammo) {}
    ~RabbitSnapshot() {}
};

#endif
