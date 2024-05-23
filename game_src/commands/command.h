#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>

#include "../../common_src/protocol.h"
#include "../constants_game.h"

/*
    * Clase que representa un comando generico.
    * Se encarga de enviar el comando a traves del protocolo.
    * Tiene un metodo que se encarga de ejecutar el comando.

    Los comandos que heredan de esta clase son:
    - Move
    - Jump
    - Shoot
    - MoveFaster
*/
class Command {
private:
    int playerID;

public:
    explicit Command(int playerID): playerID(playerID) {}

    virtual bool executeCommand(bool* cheatON, bool& needsMovement) { return true; }

    virtual void executeCommand() { return; }

    virtual void send(Protocol& protocol) = 0;
    virtual int getPlayerId() = 0;
    virtual int getCommandType() = 0;
    virtual ~Command() {}
};

#endif
