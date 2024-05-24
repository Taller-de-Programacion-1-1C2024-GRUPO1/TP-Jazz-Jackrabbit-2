#include "cheats.h"

Cheats::Cheats(int playerID, int cheatID): Command(playerID), playerID(playerID), cheatID(cheatID) {}

bool Cheats::executeCommand(bool* cheatOn, bool& needsMove) {
    if (cheatID == ADD_HEALTH) {
        // game_world.addHealthToPlayer(playerID);
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
