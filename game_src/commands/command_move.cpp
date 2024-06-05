#include "command_move.h"

Move::Move(int id, int dir): Command(id), dir(dir) {}

bool Move::execute_Command(bool* cheatOn, bool& needsMove) {
    // game_world.movePlayer(this->playerID, this->dir);
    return needsMove;
}

void Move::execute_Command(Map& map) { map.execute_move(playerID, dir); }

void Move::send(Protocol& protocol) { protocol.send_Command(this); }

int Move::get_playerId() { return this->playerID; }

int Move::get_dir() { return this->dir; }

int Move::get_commandType() { return this->commandType; }

Move::~Move() {}
