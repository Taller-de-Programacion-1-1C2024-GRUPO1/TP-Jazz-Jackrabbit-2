#ifndef RABBIT_SNAPSHOT_H
#define RABBIT_SNAPSHOT_H

class RabbitSnapshot {
public:
    int id;
    int direction;
    int champion_type;
    int pos_x;
    int pos_y;
    int score;
    int lives;
    int weapon;
    int ammo;
    int state;
    int action;

    RabbitSnapshot(int id, int direction, int champion_type, int pos_x, int pos_y, int score,
                   int lives, int weapon, int ammo, int state, int action):
            id(id),
            direction(direction),
            champion_type(champion_type),
            pos_x(pos_x),
            pos_y(pos_y),
            score(score),
            lives(lives),
            weapon(weapon),
            ammo(ammo),
            state(state),
            action(action) {}
    ~RabbitSnapshot() {}
};

#endif
