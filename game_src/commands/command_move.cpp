#include "command_move.h"

Move::Move(int id, int dir): Command(id), playerID(id), dir(dir) {}

bool Move::executeCommand(bool* cheatOn, bool& needsMove) {
    // game_world.movePlayer(this->playerID, this->dir);
    return needsMove;
}

void Move::send(Protocol& protocol) {
    // protocol.sendCommand(this);
}

int Move::getPlayerId() { return this->playerID; }

int Move::getDir() { return this->dir; }

int Move::getCommandType() { return this->commandType; }

Move::~Move() {}
