#include "command_move_faster.h"

MoveFaster::MoveFaster(int id, int dir): Command(id), playerID(id), dir(dir) {}

bool MoveFaster::execute_Command(bool* cheatOn, bool& needsMove) {
    // game_manager.moveFasterPlayer(this->playerID, this->dir);
    return needsMove;
}

int MoveFaster::get_playerId() { return this->playerID; }

int MoveFaster::get_dir() { return this->dir; }

int MoveFaster::get_commandType() { return this->commandType; }

MoveFaster::~MoveFaster() {}
