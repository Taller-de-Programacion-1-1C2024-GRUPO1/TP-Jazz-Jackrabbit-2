#include "command_change_weapon.h"

ChangeWeapon::ChangeWeapon(int id): Command(id) {}

bool ChangeWeapon::execute_Command(bool* cheatOn, bool& needsMove) {
    // game_world.change_weapon(this->playerID);
    return needsMove;
}

void ChangeWeapon::execute_Command(Rabbit& rabbit) { rabbit.change_weapon(); }

void ChangeWeapon::send(Protocol& protocol) { protocol.send_Command(this); }

int ChangeWeapon::get_playerId() { return this->playerID; }

int ChangeWeapon::get_commandType() { return this->commandType; }

ChangeWeapon::~ChangeWeapon() {}
