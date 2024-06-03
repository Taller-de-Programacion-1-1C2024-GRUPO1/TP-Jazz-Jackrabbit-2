#ifndef SPAWN_POINTS_H
#define SPAWN_POINTS_H

class SpawnPoint {

private:
    int x;
    int y;

public:
    SpawnPoint(int x, int y): x(x), y(y) {}
    ~SpawnPoint() = default;

    void set_x(int x) { this->x = x; }
    void set_y(int y) { this->y = y; }
    int get_x() const { return x; }
    int get_y() const { return y; }
};

#endif
