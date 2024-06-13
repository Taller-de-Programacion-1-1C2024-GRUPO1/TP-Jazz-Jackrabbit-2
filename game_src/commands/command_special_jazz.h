#ifndef SEPCIAL_JAZZ_H
#define SPECIAL_JAZZ_H

#include "command.h"

class Protocol;

// Clase que representa el comando de puñetazo y salto unicamente vertical en el aire
class SpecialJazz: public Command {
private:
    int commandType = COMMAND_JUMP_PUNCH_ATTACK_JAZZ;

public:
    explicit SpecialJazz(int playerID);
    void execute_Command(Rabbit& rabbit) override;
    void send(Protocol& protocol) override;
    int get_playerId() override;
    int get_dir() { return 0; }
    int get_commandType() override;
    ~SpecialJazz();
};

#endif
