#include "cheats.h"

Cheats::Cheats(int wormID, int cheatID): Command(wormID), playerID(wormID), cheatID(cheatID) {}

bool Cheats::executeCommand(bool* cheatOn, bool& needsMove) {
    if (cheatID == ADD_HEALTH) {
        // game_world.addHealthToWorm(playerID);
    }
    return needsMove;
}

void Cheats::send(Protocol& protocol) {
    // protocol.sendCommand(this);
}

int Cheats::getPlayerId() { return this->playerID; }

int Cheats::getCheatID() { return this->cheatID; }

int Cheats::getCommandType() { return this->commandType; }

Cheats::~Cheats() {}
