#ifndef MATCH_COMMAND_H
#define MATCH_COMMAND_H

#include <string>

#include "../constants_game.h"

#include "command.h"

class MatchCommand: public Command {
private:
    int type;
    int number_of_players;
    std::string match_name;
    std::string map_name;
    int commandType = COMMAND_MATCH;

public:
    MatchCommand(int type, int number_of_players, const std::string& match_name,
                 const std::string& map_name);
    int get_playerId() override;
    int getType();
    int get_number_of_players();
    std::string get_match_name();
    std::string get_map_name();
    int get_commandType() override;
    ~MatchCommand();
};

#endif
