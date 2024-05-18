#ifndef MOVE_H
#define MOVE_H

#include "command.h"

// Clase que representa el comando de moverse
class Move : public Command {

    private:
        int playerID;
        int dir;
        int commandType = COMMAND_MOVE;

    public:
        Move(int playerID, int dir);
        bool executeCommand(bool* cheatON, bool& needsMove) override;
        void send(Protocol& protocol);
        int getPlayerId();
        int getDir();
        int getCommandType();
        ~Move();
};

#endif
