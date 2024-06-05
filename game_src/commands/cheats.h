#ifndef CHEATS_H
#define CHEATS_H

#include "command.h"

class Protocol;

class Cheats: public Command {
private:
    int cheatID;
    int commandType = COMMAND_CHEAT;

public:
    Cheats(int playerID, int cheatID);
    bool execute_Command(bool* cheatON, bool& needsMove) override;
    void execute_Command(Map& map) override{};
    void send(Protocol& protocol) override;
    int get_playerId() override;
    int get_cheatID();
    int get_commandType() override;
    ~Cheats();
};

#endif
