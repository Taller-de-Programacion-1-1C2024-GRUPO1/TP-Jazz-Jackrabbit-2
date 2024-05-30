#ifndef SHOOT_H
#define SHOOT_H

#include "command.h"

// Clase que representa el comando de disparo
class Shoot: public Command {

private:
    int playerID;
    int commandType = COMMAND_SHOOT;

public:
    explicit Shoot(int playerID);
    bool execute_Command(bool* cheatON, bool& needsMove) override;
    int get_playerId() override;
    int get_commandType() override;
    ~Shoot();
};

#endif
