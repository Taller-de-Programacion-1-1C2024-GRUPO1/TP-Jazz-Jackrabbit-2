#ifndef RABBIT_SNAPSHOT_H
#define RABBIT_SNAPSHOT_H

class RabbitSnapshot {
    public:
        char id;
        float pos_x;
        float pos_y;
        int angle;
        int max_health;
        int health;
        char direction;
        int weapon;
        int state;
        int current_ammo;

        RabbitSnapshot(char id, float pos_x, float pos_y, int angle, int max_health, int health,
                    char direction, int weapon, int state, int current_ammo):
                id(id),
                pos_x(pos_x),
                pos_y(pos_y),
                angle(angle),
                max_health(max_health),
                health(health),
                direction(direction),
                weapon(weapon),
                state(state),
                current_ammo(current_ammo) {}
        ~RabbitSnapshot() {}
};

#endif
