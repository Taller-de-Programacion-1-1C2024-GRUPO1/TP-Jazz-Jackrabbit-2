#include "cheats.h"

Cheats::Cheats(int playerID, int cheatID):
        Command(playerID), playerID(playerID), cheatID(cheatID) {}

bool Cheats::execute_Command(bool* cheatOn, bool& needsMove) {
    if (cheatID == ADD_HEALTH) {
        // game_world.addHealthToPlayer(playerID);
    }
    return needsMove;
}


int Cheats::get_playerId() { return this->playerID; }

int Cheats::getCheatID() { return this->cheatID; }

int Cheats::get_commandType() { return this->commandType; }

Cheats::~Cheats() {}
