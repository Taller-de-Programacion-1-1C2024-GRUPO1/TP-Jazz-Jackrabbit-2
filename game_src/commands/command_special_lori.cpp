#include "command_special_lori.h"

SpecialLori::SpecialLori(int id, int dir): Command(id), playerID(id), dir(dir) {}

bool SpecialLori::execute_Command(bool* cheatOn, bool& needsMove) {
    if (dir == FORWARD_DIR) {
        // game_manager.special_lori(playerID);
    } else if (dir == BACKWARD_DIR) {
        // game_manager.special_lori(playerID);
    } else {
        throw std::runtime_error("Invalid direction!");
    }
}

int SpecialLori::get_playerId() { return this->playerID; }

int SpecialLori::get_dir() { return this->dir; }

int SpecialLori::get_commandType() { return this->commandType; }

SpecialLori::~SpecialLori() {}
