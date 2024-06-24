#include "command_match.h"

MatchCommand::MatchCommand(int type, int number_players, const std::string& match_name,
                           const std::string& map_name, ChampionType character_name,
                           const std::string& player_name):
        Command(PLAYING),
        type(type),
        number_players(number_players),
        match_name(match_name),
        map_name(map_name),
        character_name(character_name),
        player_name(player_name) {}

void MatchCommand::send(Protocol& protocol) { protocol.send_Command(this); }

int MatchCommand::get_playerId() { return 0; }

int MatchCommand::get_number_players() { return this->number_players; }

int MatchCommand::getType() { return this->type; }

std::string MatchCommand::get_map_name() { return this->map_name; }

std::string MatchCommand::get_match_name() { return this->match_name; }

int MatchCommand::get_commandType() { return this->commandType; }

ChampionType MatchCommand::get_character_name() { return this->character_name; }

std::string MatchCommand::get_player_name() { return this->player_name; }

MatchCommand::~MatchCommand() {}
