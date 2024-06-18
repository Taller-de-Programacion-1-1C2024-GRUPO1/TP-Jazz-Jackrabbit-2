#include "command_move_faster.h"

MoveFaster::MoveFaster(int id, int dir): Command(id), dir(dir) {}


void MoveFaster::execute_Command(Rabbit& rabbit) {
    if (dir == RIGHT) {
        rabbit.run_fast_right();
    } else {
        rabbit.run_fast_left();
    }
}

void MoveFaster::send(Protocol& protocol) { protocol.send_Command(this); }

int MoveFaster::get_playerId() { return this->playerID; }

int MoveFaster::get_dir() { return this->dir; }

int MoveFaster::get_commandType() { return this->commandType; }

MoveFaster::~MoveFaster() {}
