#include "command_shoot.h"

Shoot::Shoot(int id, int dir) : Command(id), playerID(id), dir(dir) {}

bool Shoot::executeCommand(bool* cheatOn, bool& needsMove) {
    *cheatOn = *cheatOn;
    // game_world.shootPlayer(this->playerID, this->dir);
    return needsMove;
}

void Shoot::send(Protocol& protocol) {
    // protocol.sendCommand(this);
}

int Shoot::getPlayerId() {
    return this->playerID;
}

int Shoot::getDir() {
    return this->dir;
}

int Shoot::getCommandType() {
    return this->commandType;
}

Shoot::~Shoot() {}