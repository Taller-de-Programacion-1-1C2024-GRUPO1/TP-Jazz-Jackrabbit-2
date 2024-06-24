#include "command_special_jazz.h"

SpecialJazz::SpecialJazz(int id): Command(id) {}


void SpecialJazz::execute_Command(Rabbit& rabbit) { rabbit.special_attack_jazz(); }

void SpecialJazz::send(Protocol& protocol) { protocol.send_Command(this); }

int SpecialJazz::get_playerId() { return this->playerID; }

int SpecialJazz::get_commandType() { return this->commandType; }

SpecialJazz::~SpecialJazz() {}
