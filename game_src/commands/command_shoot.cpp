#include "command_shoot.h"

Shoot::Shoot(int id): Command(id), playerID(id) {}

bool Shoot::execute_Command(bool* cheatOn, bool& needsMove) {
    // game_manager.shoot_player(this->playerID);
    return needsMove;
}

void Shoot::send(Protocol& protocol) {
    protocol.send_Command(this);
}

int Shoot::get_playerId() { return this->playerID; }

int Shoot::get_commandType() { return this->commandType; }

Shoot::~Shoot() {}
