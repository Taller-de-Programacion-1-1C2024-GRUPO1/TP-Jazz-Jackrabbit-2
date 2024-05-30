#include "command_special_spaz.h"

SpecialSpaz::SpecialSpaz(int id, int dir): Command(id), playerID(id), dir(dir) {}

bool SpecialSpaz::execute_Command(bool* cheatOn, bool& needsMove) {
    if (dir == RIGHT_DIR) {
        // game_manager.special_lori(this->playerID, this->dir);
    } else if (dir == LEFT_DIR) {
        // game_manager.special_lori(this->playerID, this->dir);
    } else {
        throw std::runtime_error("Invalid direction!");
    }
    return needsMove;
}

int SpecialSpaz::get_playerId() { return this->playerID; }

int SpecialSpaz::get_dir() { return this->dir; }

int SpecialSpaz::get_commandType() { return this->commandType; }

SpecialSpaz::~SpecialSpaz() {}
