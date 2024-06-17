#include "cheats.h"

Cheats::Cheats(int playerID, int cheatID): Command(playerID), cheatID(cheatID) {}

void Cheats::execute_Command(Rabbit& rabbit) {
    if (cheatID == MAX_AMMO) {
        rabbit.receive_max_ammo();
    } else if (cheatID == MAX_HEALTH) {
        rabbit.receive_max_health();
    } else if (cheatID == RESPAWN) {
        rabbit.respawn();
    } else if (cheatID == GODMODE) {
        rabbit.receive_god_mode();
    }
}

void Cheats::send(Protocol& protocol) { protocol.send_Command(this); }

int Cheats::get_playerId() { return this->playerID; }

int Cheats::get_cheatID() { return this->cheatID; }

int Cheats::get_commandType() { return this->commandType; }
