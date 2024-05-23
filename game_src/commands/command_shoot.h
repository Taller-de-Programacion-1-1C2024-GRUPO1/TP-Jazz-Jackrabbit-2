#ifndef SHOOT_H
#define SHOOT_H

#include "command.h"

// Clase que representa el comando de disparo
class Shoot: public Command {

private:
    int playerID;
    int dir;
    int commandType = COMMAND_SHOOT;

public:
    Shoot(int playerID, int dir);
    bool executeCommand(bool* cheatON, bool& needsMove) override;
    void send(Protocol& protocol) override;
    int getPlayerId() override;
    int getDir();
    int getCommandType() override;
    ~Shoot();
};

#endif
