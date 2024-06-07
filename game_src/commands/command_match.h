#ifndef MATCH_COMMAND_H
#define MATCH_COMMAND_H

#include <string>

#include "command.h"

class Protocol;

class MatchCommand: public Command {
private:
    int type;
    int number_players;
    std::string match_name;
    std::string map_name;
    int commandType = COMMAND_MATCH;
    ChampionType character_name;

public:
    MatchCommand(int type, int number_players, const std::string& match_name,
                 const std::string& map_name, ChampionType character_name);
    void execute_Command(Map& map) override{};
    void send(Protocol& protocol) override;
    int get_playerId() override;
    int getType();
    int get_number_players();
    std::string get_match_name();
    std::string get_map_name();
    int get_commandType() override;
    ChampionType get_character_name();
    ~MatchCommand();
};

#endif
