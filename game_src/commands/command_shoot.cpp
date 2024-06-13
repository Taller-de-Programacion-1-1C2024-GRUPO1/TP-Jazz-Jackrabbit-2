#include "command_shoot.h"

Shoot::Shoot(int id): Command(id) {}

void Shoot::execute_Command(Rabbit& rabbit) { rabbit.shoot(); }

void Shoot::send(Protocol& protocol) { protocol.send_Command(this); }

int Shoot::get_playerId() { return this->playerID; }

int Shoot::get_commandType() { return this->commandType; }

Shoot::~Shoot() {}
