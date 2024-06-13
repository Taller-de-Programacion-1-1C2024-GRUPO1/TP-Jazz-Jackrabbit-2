#ifndef MOVE_FASTER_H
#define MOVE_FASTER_H

#include "command.h"

class Protocol;

// Clase que representa el comando de moverse MUY rapido
class MoveFaster: public Command {

private:
    int dir;
    int commandType = COMMAND_MOVE_FASTER;

public:
    MoveFaster(int playerID, int dir);
    void execute_Command(Rabbit& rabbit) override;
    void send(Protocol& protocol) override;
    int get_playerId() override;
    int get_dir();
    int get_commandType() override;
    ~MoveFaster();
};

#endif
