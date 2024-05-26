#ifndef MOVE_H
#define MOVE_H

#include "command.h"

// Clase que representa el comando de moverse
class Move: public Command {

private:
    int playerID;
    int dir;
    int commandType = COMMAND_MOVE;

public:
    Move(int playerID, int dir);
    bool execute_Command(bool* cheatON, bool& needsMove) override;
    int get_playerId() override;
    int get_dir();
    int get_commandType() override;
    ~Move();
};

#endif
