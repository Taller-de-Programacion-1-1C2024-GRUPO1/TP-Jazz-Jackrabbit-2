#ifndef CHEATS_H
#define CHEATS_H

#include "command.h"

class Cheats : public Command {
    private:
        int playerID;
        int cheatID;
        int commandType = COMMAND_CHEAT;

    public: 
        Cheats(int playerID, int cheatID);
        bool executeCommand(bool* cheatON, bool& needsMove) override;
        void send(Protocol& protocol);
        int getPlayerId();
        int getCheatID();
        int getCommandType();
        ~Cheats();
};

#endif
