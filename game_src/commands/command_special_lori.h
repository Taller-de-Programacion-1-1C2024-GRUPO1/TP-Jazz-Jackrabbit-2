#ifndef SEPCIAL_LORI_H
#define SPECIAL_LORI_H

#include "command.h"

class Protocol;

// Clase que representa el comando de patada voladora de corto alcance de Lori
class SpecialLori: public Command {
private:
    int dir;
    int commandType = COMMANDS_SHORT_RANGE_JUMP_KICK_LORI;

public:
    SpecialLori(int playerID, int dir);
    void execute_Command(Rabbit& rabbit) override;
    void send(Protocol& protocol) override;
    int get_playerId() override;
    int get_dir();
    int get_commandType() override;
    ~SpecialLori();
};

#endif
