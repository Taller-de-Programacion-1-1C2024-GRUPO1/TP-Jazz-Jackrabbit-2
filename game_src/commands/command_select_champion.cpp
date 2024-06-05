#include "command_select_champion.h"

SelectChampion::SelectChampion(int playerID, ChampionType champion_type,
                               const std::string& match_name, const std::string& map_name):
        Command(playerID),
        champion_type(champion_type),
        match_name(match_name),
        map_name(map_name) {}

void SelectChampion::send(Protocol& protocol) { protocol.send_Command(this); }

int SelectChampion::get_playerId() { return playerID; }

ChampionType SelectChampion::get_championType() { return this->champion_type; }

std::string SelectChampion::get_map_name() { return this->map_name; }

std::string SelectChampion::get_match_name() { return this->match_name; }

int SelectChampion::get_commandType() { return this->commandType; }

SelectChampion::~SelectChampion() {}
