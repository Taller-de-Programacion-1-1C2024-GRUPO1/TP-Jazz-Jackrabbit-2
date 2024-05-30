#ifndef COMMON_PROTOCOLO_H
#define COMMON_PROTOCOLO_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "../game_src/commands/cheats.h"
#include "../game_src/commands/command_change_weapon.h"
#include "../game_src/commands/command_jump.h"
#include "../game_src/commands/command_match.h"
#include "../game_src/commands/command_move.h"
#include "../game_src/commands/command_move_faster.h"
#include "../game_src/commands/command_select_champion.h"
#include "../game_src/commands/command_shoot.h"
#include "../game_src/commands/command_special_jazz.h"
#include "../game_src/commands/command_special_lori.h"
#include "../game_src/commands/command_special_spaz.h"
#include "../game_src/constants_game.h"
#include "../game_src/entities/bullet.h"
#include "../game_src/entities/character.h"
#include "../game_src/entities/item.h"
#include "../game_src/entities/player.h"
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

    void send_Match(MatchCommand* match);

    void send_Cheat(Cheats* cheat);

    void send_ChangeWeapon(ChangeWeapon* changeWeapon);

    void send_SelectChampion(SelectChampion* selectChampion);

    void send_SpecialJazz(SpecialJazz* specialJazz);

    void send_SpecialLori(SpecialLori* specialLori);

    void send_SpecialSpaz(SpecialSpaz* specialSpaz);

    std::shared_ptr<Move> receive_Move();

    std::shared_ptr<MoveFaster> receive_MoveFaster();

    std::shared_ptr<Jump> receive_Jump();

    std::shared_ptr<Shoot> receive_Shoot();

    std::shared_ptr<MatchCommand> receive_Match();

    std::shared_ptr<Cheats> receive_Cheat();

    std::shared_ptr<ChangeWeapon> receive_ChangeWeapon();

    std::shared_ptr<SelectChampion> receive_SelectChampion();

    std::shared_ptr<SpecialJazz> receive_SpecialJazz();

    std::shared_ptr<SpecialLori> receive_SpecialLori();

    std::shared_ptr<SpecialSpaz> receive_SpecialSpaz();

    // ------------------- SEND AND RECEIVE SNAPSHOTS -------------------

    void send_dimensions(const Snapshot& snapshot);

    void send_rabbits(Snapshot& snapshot);

    void send_projectiles(Snapshot& snapshot);

    void send_supplies(Snapshot& snapshot);

    void receive_dimensions(Snapshot& snapshot);

    void receive_rabbits(Snapshot& snapshot);

    void receive_projectiles(Snapshot& snapshot);

    void receive_supplies(Snapshot& snapshot);

public:
    // Constructor para el cliente
    Protocol(const std::string& host, const std::string& service);

    // Constructor para el server
    explicit Protocol(Socket peer);

    // ------------------- Funciones para Server -------------------

    // Recibe un comando
    std::shared_ptr<Command> receive_Command();

    // Envia un Snapshot
    void send_Snapshot(Snapshot& snapshot);

    // ------------------- Funciones para Client -------------------

    // Envia un comando
    void send_Command(Command* command);

    // Recibe un Snapshot
    Snapshot receive_Snapshot();

    // ------------------- Funciones para Client y Server -------------------

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

    // Envia un ACK de que un jugador se unio a un match
    void send_user_joined_match(int ACK_JOINED);
    int receive_user_joined_match();

    // Chequea si el socket fue cerrado
    bool is_close();

    // Chequea si el socket fue cerrado y si es asi, lanza una excepcion
    void check_closed();

    ~Protocol();
};

#endif
