#ifndef SHOOT_H
#define SHOOT_H

#include "command.h"

class Protocol;

// Clase que representa el comando de disparo
class Shoot: public Command {

private:
    int commandType = COMMAND_SHOOT;

public:
    explicit Shoot(int playerID);
    void execute_Command(Rabbit& rabbit) override;
    void send(Protocol& protocol) override;
    int get_playerId() override;
    int get_commandType() override;
    ~Shoot();
};

#endif
