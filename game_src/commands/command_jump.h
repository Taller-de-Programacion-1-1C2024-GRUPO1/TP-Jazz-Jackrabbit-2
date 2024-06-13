#ifndef JUMP_H
#define JUMP_H

#include "command.h"

class Protocol;

// Clase que representa el comando de salto
class Jump: public Command {
private:
    int dir;
    int commandType = COMMAND_JUMP;

public:
    Jump(int playerID, int dir);
    void execute_Command(Rabbit& rabbit) override;
    void send(Protocol& protocol) override;
    int get_playerId() override;
    int get_dir();
    int get_commandType() override;
    ~Jump();
};

#endif
