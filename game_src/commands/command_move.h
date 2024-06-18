#ifndef MOVE_H
#define MOVE_H

#include "command.h"

class Protocol;

// Clase que representa el comando de moverse
class Move: public Command {

private:
    int dir;
    int commandType = COMMAND_MOVE;

public:
    Move(int playerID, int dir);
    void execute_Command(Rabbit& rabbit) override;
    void send(Protocol& protocol) override;
    int get_playerId() override;
    int get_dir();
    int get_commandType() override;
    ~Move();
};

#endif
