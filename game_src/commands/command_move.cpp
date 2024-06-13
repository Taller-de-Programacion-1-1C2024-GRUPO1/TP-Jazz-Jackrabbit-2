#include "command_move.h"

Move::Move(int id, int dir): Command(id), dir(dir) {}

void Move::execute_Command(Rabbit& rabbit) {
    if (dir == RIGHT) {
        rabbit.run_right();
    } else {
        rabbit.run_left();
    }
}

void Move::send(Protocol& protocol) { protocol.send_Command(this); }

int Move::get_playerId() { return this->playerID; }

int Move::get_dir() { return this->dir; }

int Move::get_commandType() { return this->commandType; }

Move::~Move() {}
