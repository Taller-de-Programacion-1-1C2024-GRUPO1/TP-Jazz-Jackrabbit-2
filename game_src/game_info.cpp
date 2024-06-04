#include "game_info.h"

#include "../common_src/protocol.h"

GameInfo::GameInfo(std::map<std::string, std::string> matchesAvailable):
        matchesAvailable(matchesAvailable) {}

void GameInfo::send(Protocol& protocol) { protocol.send_Info(this); }

int GameInfo::get_infoType() { return InfoType; }

std::map<std::string, std::string> GameInfo::getMatchesAvailable() { return matchesAvailable; }
