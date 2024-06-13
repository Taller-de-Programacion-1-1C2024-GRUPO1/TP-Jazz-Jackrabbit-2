#ifndef SEPCIAL_SPAZ_H
#define SPECIAL_SPAZ_H

#include "command.h"

class Protocol;

// Clase que representa el comando de patada lateral sobre el suelo de Spazz
class SpecialSpaz: public Command {
private:
    int dir;
    int commandType = COMMANDS_SIDE_KICK_SPAZ;

public:
    SpecialSpaz(int playerID, int dir);
    void execute_Command(Rabbit& rabbit) override;
    int get_playerId() override;
    void send(Protocol& protocol) override;
    int get_dir();
    int get_commandType() override;
    ~SpecialSpaz();
};

#endif
