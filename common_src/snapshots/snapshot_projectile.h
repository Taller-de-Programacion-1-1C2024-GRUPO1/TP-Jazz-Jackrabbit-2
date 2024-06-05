#ifndef PROJECTILE_SNAPSHOT_H
#define PROJECTILE_SNAPSHOT_H

class ProjectileSnapshot {
public:
    int id;
    int weapon;
    int pos_x;
    int pos_y;
    int state;

    ProjectileSnapshot(int id, int weapon, int pos_x, int pos_y, int state):
            id(id), weapon(weapon), pos_x(pos_x), pos_y(pos_y), state(state) {}
};

#endif
