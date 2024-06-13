#ifndef CHANGE_WEAPON_H
#define CHANGE_WEAPON_H

#include "command.h"

class Protocol;

// Clase que representa el comando de cambiar de arma/municion
class ChangeWeapon: public Command {
private:
    int commandType = COMMAND_CHANGE_WEAPON;

public:
    explicit ChangeWeapon(int playerID);
    void execute_Command(Rabbit& rabbit) override;
    void send(Protocol& protocol) override;
    int get_playerId() override;
    int get_commandType() override;
    ~ChangeWeapon();
};

#endif
