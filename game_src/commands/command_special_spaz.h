#ifndef SEPCIAL_SPAZ_H
#define SPECIAL_SPAZ_H

#include "command.h"

// Clase que representa el comando de patada lateral sobre el suelo de Spazz
class SpecialSpaz: public Command {
private:
    int playerID;
    int dir;
    int commandType = COMMANDS_SIDE_KICK_SPAZ;

public:
    SpecialSpaz(int playerID, int dir);
    bool execute_Command(bool* cheatON, bool& needsMove) override;
    int get_playerId() override;
    int get_dir();
    int get_commandType() override;
    ~SpecialSpaz();
};

#endif
