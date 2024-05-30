#include "command_match.h"

MatchCommand::MatchCommand(int type, const std::string& match_name, const std::string& map_name):
        Command(PLAYING), type(type), match_name(match_name), map_name(map_name) {}

int MatchCommand::get_playerId() { return 0; }

int MatchCommand::getType() { return this->type; }

std::string MatchCommand::get_map_name() { return this->map_name; }

std::string MatchCommand::get_match_name() { return this->match_name; }

int MatchCommand::get_commandType() { return this->commandType; }

MatchCommand::~MatchCommand() {}
