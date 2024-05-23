#ifndef COMMON_PROTOCOLO_H
#define COMMON_PROTOCOLO_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "../game_src/commands/cheats.h"
#include "../game_src/commands/command_jump.h"
#include "../game_src/commands/command_match.h"
#include "../game_src/commands/command_move.h"
#include "../game_src/commands/command_move_faster.h"
#include "../game_src/commands/command_shoot.h"
#include "snapshots/snapshot.h"

#include "common_errors.h"
#include "common_socket.h"
#include "constants.h"

class Protocol {
protected:
    const std::string hostname;
    const std::string servname;
    Socket socket;
    bool was_closed = false;

private:
    // ------------------- SEND AND RECEIVE COMMANDS -------------------
    void send_Move(Move* move);

    void send_MoveFaster(MoveFaster* moveFaster);

    void send_Jump(Jump* jump);

    void send_Shoot(Shoot* shoot);

    // void send_Match(Match* match);

    // void send_Cheat(Cheats* cheat);

    std::shared_ptr<Move> receive_Move();

    std::shared_ptr<MoveFaster> receive_MoveFaster();

    std::shared_ptr<Jump> receive_Jump();

    std::shared_ptr<Shoot> receive_Shoot();

    // std::shared_ptr<Match> receive_Match();

    // std::shared_ptr<Cheats> receive_Cheat();

    // ------------------- SEND AND RECEIVE SNAPSHOTS -------------------

    void send_dimensions(const Snapshot& snapshot);

    void send_rabbits(const Snapshot& snapshot);

    void send_projectiles(const Snapshot& snapshot);

    void send_supplies(const Snapshot& snapshot);

    void receive_dimensions(const Snapshot& snapshot);

    void receive_rabbits(const Snapshot& snapshot);

    void receive_projectiles(const Snapshot& snapshot);

    void receive_supplies(const Snapshot& snapshot);

public:
    // Constructor para el cliente
    Protocol(const std::string& host, const std::string& service);

    // Constructor para el server
    explicit Protocol(Socket peer);

    // ------------------- Funciones para Server -------------------

    // Recibe un comando
    std::shared_ptr<Command> receive_Command();

    // Envia un Snapshot
    void send_Snapshot(const Snapshot& snapshot);

    // ------------------- Funciones para Client -------------------

    // Envia un comando
    void send_Command(Command* command);

    // Recibe un Snapshot
    Snapshot receive_Snapshot();

    // ------------------- Funciones para Client y Server -------------------

    // Envia un float
    void send_float(float num);
    float receive_float();

    // Envia un uint8_t
    void send_uintEight(uint8_t num);
    uint8_t receive_uintEight();

    // Envia un uint16_t
    void send_uintSixteen(uint16_t num);
    uint16_t receive_uintSixteen();

    // Envia un uint32_t
    void send_uintThirtyTwo(uint32_t num);
    uint32_t receive_uintThirtyTwo();

    // Envia un string
    void send_string(const std::string& str);
    std::string receive_string();

    // Envia un char
    void send_char(char c);
    char receive_char();

    // Chequea si el socket fue cerrado
    bool is_close();

    // Chequea si el socket fue cerrado y si es asi, lanza una excepcion
    void check_closed();

    ~Protocol();
};

#endif
