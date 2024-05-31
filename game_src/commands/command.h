#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>

#include "../../common_src/constants.h"
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
    - MatchCommand
    - Cheats
    - ChangeWeapon
    - SelectChampion
    - SpecialJazz
    - SpecialLori
    - SpecialSpaz
*/
class Command {
private:
    int playerID;

public:
    explicit Command(int playerID): playerID(playerID) {}

    virtual bool execute_Command(bool* cheatON, bool& needsMovement) = 0;

    virtual void execute_Command() = 0;

    virtual int get_playerId() = 0;
    virtual int get_commandType() = 0;
    virtual ~Command() {}
};

#endif
