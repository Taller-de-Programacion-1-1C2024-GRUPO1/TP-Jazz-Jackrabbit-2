#ifndef CHANGE_WEAPON_H
#define CHANGE_WEAPON_H

#include "command.h"

class Protocol;

// Clase que representa el comando de cambiar de arma/municion
class ChangeWeapon: public Command {
private:
    int playerID;
    int commandType = COMMAND_CHANGE_WEAPON;

public:
    explicit ChangeWeapon(int playerID);
    bool execute_Command(bool* cheatON, bool& needsMove) override;
    void send(Protocol& protocol);
    int get_playerId() override;
    int get_commandType() override;
    ~ChangeWeapon();
};

#endif
