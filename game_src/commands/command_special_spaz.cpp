#include "command_special_spaz.h"

SpecialSpaz::SpecialSpaz(int id, int dir): Command(id), dir(dir) {}


void SpecialSpaz::execute_Command(Rabbit& rabbit) { rabbit.special_attack_spaz(dir); }

void SpecialSpaz::send(Protocol& protocol) { protocol.send_Command(this); }

int SpecialSpaz::get_playerId() { return this->playerID; }

int SpecialSpaz::get_dir() { return this->dir; }

int SpecialSpaz::get_commandType() { return this->commandType; }

SpecialSpaz::~SpecialSpaz() {}
