#ifndef MATCH_COMMAND_H
#define MATCH_COMMAND_H

#include <string>

#include "command.h"

// Comando que crea partidas (se usaría en un futuro probablemente)
class Match: public Command {
private:
    int type;
    // int nrPlayers;
    std::string match;
    std::string map;
    int commandType = COMMAND_MATCH;

public:
    Match(int type, std::string match, std::string map);
    ~Match();
    int get_playerId() override;
    int getType();
    // int getNrPlayers();
    std::string getMatchName();
    std::string getMapName();
    int get_commandType() override;
};

#endif
