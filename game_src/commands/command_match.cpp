#include "command_match.h"

MatchCommand::MatchCommand(int type, int number_of_players, const std::string& match_name,
                           const std::string& map_name):
        Command(PLAYING),
        type(type),
        number_of_players(number_of_players),
        match_name(match_name),
        map_name(map_name) {}

int MatchCommand::get_playerId() { return 0; }

int MatchCommand::getType() { return this->type; }

int MatchCommand::get_number_of_players() { return this->number_of_players; }

std::string MatchCommand::get_map_name() { return this->map_name; }

std::string MatchCommand::get_match_name() { return this->match_name; }

int MatchCommand::get_commandType() { return this->commandType; }

MatchCommand::~MatchCommand() {}
