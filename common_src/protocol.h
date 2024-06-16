#ifndef COMMON_PROTOCOLO_H
#define COMMON_PROTOCOLO_H

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "../game_src/constants_game.h"
#include "../game_src/entities/bullet.h"
#include "../game_src/entities/character.h"
#include "../game_src/entities/item.h"
#include "../game_src/entities/rabbit.h"
#include "snapshots/snapshot.h"

#include "common_errors.h"
#include "common_socket.h"
#include "constants.h"

class Command;
class Move;
class MoveFaster;
class Jump;
class Shoot;
class MatchCommand;
class Cheats;
class ChangeWeapon;
class SelectChampion;
class SpecialJazz;
class SpecialLori;
class SpecialSpaz;
class DynamicMap;
class QtResponse;


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

    std::unique_ptr<Move> receive_Move();

    std::unique_ptr<MoveFaster> receive_MoveFaster();

    std::unique_ptr<Jump> receive_Jump();

    std::unique_ptr<Shoot> receive_Shoot();

    std::unique_ptr<MatchCommand> receive_Match();

    std::unique_ptr<Cheats> receive_Cheat();

    std::unique_ptr<ChangeWeapon> receive_ChangeWeapon();

    std::unique_ptr<SelectChampion> receive_SelectChampion();

    std::unique_ptr<SpecialJazz> receive_SpecialJazz();

    std::unique_ptr<SpecialLori> receive_SpecialLori();

    std::unique_ptr<SpecialSpaz> receive_SpecialSpaz();

    // ------------------- SEND AND RECEIVE SNAPSHOTS -------------------

    void send_dimensions(const Snapshot& snapshot);

    void send_rabbits(Snapshot& snapshot);

    void send_enemies(Snapshot& snapshot);

    void send_projectiles(Snapshot& snapshot);

    void send_supplies(Snapshot& snapshot);

    void receive_dimensions(Snapshot& snapshot);

    void receive_rabbits(Snapshot& snapshot);

    void receive_enemies(Snapshot& snapshot);

    void receive_projectiles(Snapshot& snapshot);

    void receive_supplies(Snapshot& snapshot);

public:
    // Constructor para el cliente
    Protocol(const std::string& host, const std::string& service);

    // Constructor para el server
    explicit Protocol(Socket peer);

    // ------------------- Funciones para Server -------------------

    // Recibe un comando
    std::unique_ptr<Command> receive_Command();

    // Envia un Snapshot
    void send_Snapshot(Snapshot& snapshot);


    // ------------------- Funciones para Client -------------------

    // Envia un comando
    void send_Command(Command* command);

    // Recibe un Snapshot
    Snapshot receive_Snapshot();

    // ------------------- SEND AND RECEIVE INFO -------------------

    void send_info_available(
            std::tuple<std::vector<std::string>, std::vector<std::string>> info_available);
    std::tuple<std::vector<std::string>, std::vector<std::string>> receive_info_available();


    void send_qt_response(QtResponse* qt_response);

    std::unique_ptr<QtResponse> receive_qt_response();

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

    // Envia un DynamicMap
    void send_map(int width, int heigth, DynamicMap map);
    DynamicMap receive_map();

    // Chequea si el socket fue cerrado
    bool is_close();

    // Chequea si el socket fue cerrado y si es asi, lanza una excepcion
    void check_closed();

    // Rompe de forma adecuada las conexiones con el protocolo
    void kill();

    ~Protocol();
};

#endif
