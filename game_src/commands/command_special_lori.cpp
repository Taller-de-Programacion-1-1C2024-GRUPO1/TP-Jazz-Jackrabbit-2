#include "command_special_lori.h"

SpecialLori::SpecialLori(int id, int dir): Command(id), dir(dir) {}


void SpecialLori::execute_Command(Rabbit& rabbit) { rabbit.special_attack_lori(); }

void SpecialLori::send(Protocol& protocol) { protocol.send_Command(this); }

int SpecialLori::get_playerId() { return this->playerID; }

int SpecialLori::get_dir() { return this->dir; }

int SpecialLori::get_commandType() { return this->commandType; }

SpecialLori::~SpecialLori() {}
