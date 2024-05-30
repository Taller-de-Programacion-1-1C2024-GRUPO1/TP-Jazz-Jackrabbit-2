#include "command_special_jazz.h"

SpecialJazz::SpecialJazz(int id): Command(id), playerID(id) {}

bool SpecialJazz::execute_Command(bool* cheatOn, bool& needsMove) {
    // game_manager.specialJazzPlayer(this->playerID);
    return needsMove;
}

int SpecialJazz::get_playerId() { return this->playerID; }

int SpecialJazz::get_commandType() { return this->commandType; }

SpecialJazz::~SpecialJazz() {}
