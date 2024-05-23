#ifndef MOVE_H
#define MOVE_H

#include "command.h"

// Clase que representa el comando de moverse MUY rapido
class MoveFaster: public Command {

private:
    int playerID;
    int dir;
    int commandType = COMMAND_MOVE_FASTER;

public:
    MoveFaster(int playerID, int dir);
    bool executeCommand(bool* cheatON, bool& needsMove) override;
    void send(Protocol& protocol) override;
    int getPlayerId() override;
    int getDir();
    int getCommandType() override;
    ~MoveFaster();
};

#endif
