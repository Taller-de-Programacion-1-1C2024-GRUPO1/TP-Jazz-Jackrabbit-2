#include "command_jump.h"

Jump::Jump(int id, int dir): Command(id), playerID(id), dir(dir) {}

bool Jump::executeCommand(bool* cheatOn, bool& needsMove) {
    if (dir == FORWARD_DIR) {
        // game_world.jumpForwardPlayer(playerID);
    } else if (dir == BACKWARD_DIR) {
        // game_world.jumpBackwardsPlayer(playerID);
    } else {
        throw std::runtime_error("Invalid direction!");
    }
    return needsMove;
}

void Jump::send(Protocol& protocol) {
    // protocol.sendCommand(this);
}

int Jump::getPlayerId() { return this->playerID; }

int Jump::getDir() { return this->dir; }

int Jump::getCommandType() { return this->commandType; }

Jump::~Jump() {}
