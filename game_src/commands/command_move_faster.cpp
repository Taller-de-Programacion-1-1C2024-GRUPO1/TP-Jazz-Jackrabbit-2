#include "command_move_faster.h"

MoveFaster::MoveFaster(int id, int dir): Command(id), playerID(id), dir(dir) {}

bool MoveFaster::executeCommand(bool* cheatOn, bool& needsMove) {
    // game_world.moveFasterPlayer(this->playerID, this->dir);
    return needsMove;
}

void MoveFaster::send(Protocol& protocol) {
    // protocol.sendCommand(this);
}

int MoveFaster::getPlayerId() { return this->playerID; }

int MoveFaster::getDir() { return this->dir; }

int MoveFaster::getCommandType() { return this->commandType; }

MoveFaster::~MoveFaster() {}
