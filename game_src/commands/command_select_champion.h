#ifndef SELECT_CHAMPION_H
#define SELECT_CHAMPION_H

#include <string>

#include "../constants_game.h"

#include "command.h"

class SelectChampion: public Command {
private:
    int playerID;
    ChampionType champion_type;
    std::string match_name;
    std::string map_name;
    int commandType = COMMAND_SELECT_CHAMPION;

public:
    SelectChampion(int playerID, ChampionType champion_type, const std::string& match_name,
                 const std::string& map_name);
    int get_playerId() override;
    ChampionType get_championType();
    std::string get_match_name();
    std::string get_map_name();
    int get_commandType() override;
    ~SelectChampion();
};

#endif
