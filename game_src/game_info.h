#ifndef GAME_INFO_H
#define GAME_INFO_H

#include <iostream>
#include <map>
#include <string>

#include "information.h"

class Protocol;

class GameInfo: public Information {
private:
    std::map<std::string, std::string> matchesAvailable;
    int InfoType = GAME_INFO;

public:
    explicit GameInfo(std::map<std::string, std::string> matchesAvailable);
    void send(Protocol& protocol) override;
    int get_infoType() override;
    std::map<std::string, std::string> getMatchesAvailable();
};

#endif
