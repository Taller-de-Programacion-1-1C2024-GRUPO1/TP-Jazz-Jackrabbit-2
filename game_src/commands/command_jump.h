#ifndef JUMP_H
#define JUMP_H

#include "command.h"

// Clase que representa el comando de salto
class Jump: public Command {
private:
    int playerID;
    int dir;
    int commandType = COMMAND_JUMP;

public:
    Jump(int playerID, int dir);
    bool executeCommand(bool* cheatON, bool& needsMove) override;
    void send(Protocol& protocol) override;
    int getPlayerId() override;
    int getDir();
    int getCommandType() override;
    ~Jump();
};

#endif
