#include "command_shoot.h"

Shoot::Shoot(int id, int dir): Command(id), playerID(id), dir(dir) {}

bool Shoot::execute_Command(bool* cheatOn, bool& needsMove) {
    // game_manager.shoot_player(this->playerID, this->dir);
    return needsMove;
}

int Shoot::get_playerId() { return this->playerID; }

int Shoot::get_dir() { return this->dir; }

int Shoot::get_commandType() { return this->commandType; }

Shoot::~Shoot() {}
