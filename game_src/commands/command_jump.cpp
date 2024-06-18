#include "command_jump.h"

Jump::Jump(int id, int dir): Command(id), dir(dir) {}

void Jump::execute_Command(Rabbit& rabbit) { rabbit.jump(); }


void Jump::send(Protocol& protocol) { protocol.send_Command(this); }

int Jump::get_playerId() { return this->playerID; }

int Jump::get_dir() { return this->dir; }

int Jump::get_commandType() { return this->commandType; }

Jump::~Jump() {}
