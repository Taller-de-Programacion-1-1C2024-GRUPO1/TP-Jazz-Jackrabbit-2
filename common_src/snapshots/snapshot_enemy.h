#ifndef SNAPSHOT_ENEMY_H
#define SNAPSHOT_ENEMY_H

class EnemySnapshot {
public:
    int id;
    int direction;
    int enemy_type;
    int pos_x;
    int pos_y;

    EnemySnapshot(int id, int direction, int enemy_type, int pos_x, int pos_y):
            id(id), direction(direction), enemy_type(enemy_type), pos_x(pos_x), pos_y(pos_y) {}
};

#endif
