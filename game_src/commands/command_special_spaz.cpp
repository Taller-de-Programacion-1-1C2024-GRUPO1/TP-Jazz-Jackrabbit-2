#include "command_special_spaz.h"

SpecialSpaz::SpecialSpaz(int id, int dir): Command(id), playerID(id), dir(dir) {}

bool SpecialSpaz::execute_Command(bool* cheatOn, bool& needsMove) {
    if (dir == FORWARD_DIR) {
        // game_manager.special_lori(playerID);
    } else if (dir == BACKWARD_DIR) {
        // game_manager.special_lori(playerID);
    } else {
        throw std::runtime_error("Invalid direction!");
    }
}

int SpecialSpaz::get_playerId() { return this->playerID; }

int SpecialSpaz::get_dir() { return this->dir; }

int SpecialSpaz::get_commandType() { return this->commandType; }

SpecialSpaz::~SpecialSpaz() {}
