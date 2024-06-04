#ifndef JUMP_H
#define JUMP_H

#include "command.h"

class Protocol;

// Clase que representa el comando de salto
class Jump: public Command {
private:
    int playerID;
    int dir;
    int commandType = COMMAND_JUMP;

public:
    Jump(int playerID, int dir);
    bool execute_Command(bool* cheatON, bool& needsMove) override;
    void send(Protocol& protocol);
    int get_playerId() override;
    int get_dir();
    int get_commandType() override;
    ~Jump();
};

#endif
