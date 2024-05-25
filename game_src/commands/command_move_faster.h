#ifndef MOVE_FASTER_H
#define MOVE_FASTER_H

#include "command.h"

// Clase que representa el comando de moverse MUY rapido
class MoveFaster: public Command {

private:
    int playerID;
    int dir;
    int commandType = COMMAND_MOVE_FASTER;

public:
    MoveFaster(int playerID, int dir);
    bool execute_Command(bool* cheatON, bool& needsMove) override;
    int get_playerId() override;
    int get_dir();
    int get_commandType() override;
    ~MoveFaster();
};

#endif
