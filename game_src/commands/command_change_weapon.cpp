#include "command_change_weapon.h"

ChangeWeapon::ChangeWeapon(int id): Command(id) {}

void ChangeWeapon::execute_Command(Rabbit& rabbit) { rabbit.change_weapon(); }

void ChangeWeapon::send(Protocol& protocol) { protocol.send_Command(this); }

int ChangeWeapon::get_playerId() { return this->playerID; }

int ChangeWeapon::get_commandType() { return this->commandType; }

ChangeWeapon::~ChangeWeapon() {}
