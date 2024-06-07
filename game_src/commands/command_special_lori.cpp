#include "command_special_lori.h"

SpecialLori::SpecialLori(int id, int dir): Command(id), dir(dir) {}

bool SpecialLori::execute_Command(bool* cheatOn, bool& needsMove) {
    if (dir == UP) {
        // game_manager.special_lori(playerID);
    } else if (dir == DOWN) {
        // game_manager.special_lori(playerID);
    } else {
        throw std::runtime_error("Invalid direction!");
    }
    return needsMove;
}

void SpecialLori::send(Protocol& protocol) { protocol.send_Command(this); }

int SpecialLori::get_playerId() { return this->playerID; }

int SpecialLori::get_dir() { return this->dir; }

int SpecialLori::get_commandType() { return this->commandType; }

SpecialLori::~SpecialLori() {}
