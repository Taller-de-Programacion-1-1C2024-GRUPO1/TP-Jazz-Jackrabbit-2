#include "command_jump.h"

Jump::Jump(int id, int dir): Command(id), dir(dir) {}

void Jump::execute_Command(Map& map) { map.execute_jump(playerID); }

/*
bool Jump::execute_Command(bool* cheatOn, bool& needsMove) {
    if (dir == RIGHT_DIR) {
        // game_manager.jumpForwardPlayer(playerID);
    } else if (dir == LEFT_DIR) {
        // game_manager.jumpBackwardsPlayer(playerID);
    } else {
        throw std::runtime_error("Invalid direction!");
    }
    return needsMove;
}
*/

void Jump::send(Protocol& protocol) { protocol.send_Command(this); }

int Jump::get_playerId() { return this->playerID; }

int Jump::get_dir() { return this->dir; }

int Jump::get_commandType() { return this->commandType; }

Jump::~Jump() {}
