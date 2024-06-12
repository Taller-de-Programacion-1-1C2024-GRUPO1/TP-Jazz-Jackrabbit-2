#ifndef SELECT_CHAMPION_H
#define SELECT_CHAMPION_H

#include <string>

#include "command.h"

class Protocol;

class SelectChampion: public Command {
private:
    ChampionType champion_type;
    std::string match_name;
    std::string map_name;
    int commandType = COMMAND_SELECT_CHAMPION;

public:
    SelectChampion(int playerID, ChampionType champion_type, const std::string& match_name,
                   const std::string& map_name);
    int get_playerId() override;
    void execute_Command(Rabbit& rabbit) override{};
    void send(Protocol& protocol) override;
    ChampionType get_championType();
    std::string get_match_name();
    std::string get_map_name();
    int get_commandType() override;
    ~SelectChampion();
};

#endif
