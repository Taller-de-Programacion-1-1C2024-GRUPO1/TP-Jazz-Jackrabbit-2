#include "cheats.h"

Cheats::Cheats(int playerID, int cheatID): Command(playerID), cheatID(cheatID) {}

void Cheats::send(Protocol& protocol) { protocol.send_Command(this); }

int Cheats::get_playerId() { return this->playerID; }

int Cheats::get_cheatID() { return this->cheatID; }

int Cheats::get_commandType() { return this->commandType; }

Cheats::~Cheats() {}
