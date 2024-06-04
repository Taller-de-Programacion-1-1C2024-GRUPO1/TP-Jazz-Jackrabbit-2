#include "protocol.h"

#include "../game_src/commands/cheats.h"
#include "../game_src/commands/command.h"
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
#include "../game_src/game_info.h"
#include "../game_src/information.h"

// Protocol
Protocol::Protocol(const std::string& host, const std::string& service):
        hostname(host), servname(service), socket(host.c_str(), service.c_str()) {}


Protocol::Protocol(Socket peer): socket(std::move(peer)), was_closed(false) {}


// ----------------------------- SEND BYTES/STRING/CHAR/ACK -----------------------------

void Protocol::send_uintEight(uint8_t num) {
    socket.sendall(&num, sizeof(num), &was_closed);
    check_closed();
}

void Protocol::send_uintSixteen(uint16_t num) {
    uint16_t num_htons = htons(num);
    socket.sendall(&num_htons, sizeof(num_htons), &was_closed);
    check_closed();
}

void Protocol::send_uintThirtyTwo(uint32_t num) {
    uint32_t num_htonl = htonl(num);
    socket.sendall(&num_htonl, sizeof(num_htonl), &was_closed);
    check_closed();
}

void Protocol::send_string(const std::string& str) {
    send_uintSixteen(str.size());
    socket.sendall(str.c_str(), str.size(), &was_closed);
    check_closed();
}

void Protocol::send_char(char c) {
    socket.sendall(&c, sizeof(c), &was_closed);
    check_closed();
}


// Primer Response:
// envia un ACK 0 en caso de haberse unido/creado un match
// envia un ACK negativo (-1) en caso de no poder unirse/crear un match
// Segundo response:
// envia un ACK positivo (player_id) justo antes de iniciar la match
void Protocol::send_response(int ACK_JOINED) {
    check_closed();
    send_uintEight(ACK_JOINED);
}

// ----------------------------- RECEIVE BYTES/STRINGS/CHAR/ACK -----------------------------

uint8_t Protocol::receive_uintEight() {
    uint8_t num;
    socket.recvall(&num, sizeof(num), &was_closed);
    check_closed();
    return num;
}

uint16_t Protocol::receive_uintSixteen() {
    uint16_t num;
    socket.recvall(&num, sizeof(num), &was_closed);
    check_closed();
    return ntohs(num);
}

uint32_t Protocol::receive_uintThirtyTwo() {
    uint32_t num;
    socket.recvall(&num, sizeof(num), &was_closed);
    check_closed();
    return ntohl(num);
}

std::string Protocol::receive_string() {
    uint16_t length_string = receive_uintSixteen();
    std::string str(length_string, '\0');
    socket.recvall((void*)str.data(), length_string, &was_closed);
    check_closed();
    return str;
}

char Protocol::receive_char() {
    char c;
    socket.recvall(&c, sizeof(c), &was_closed);
    check_closed();
    return c;
}


// Primer Response:
// recibe un ACK 0 en caso de haberse unido/creado un match
// recibe un ACK negativo (-1) en caso de no poder unirse/crear un match
// Segundo response:
// recibe un ACK positivo (player_id) justo antes de iniciar la match
int Protocol::receive_response() {
    check_closed();
    uint8_t ACK_JOINED = receive_uintEight();
    return ACK_JOINED;
}

bool Protocol::is_close() { return this->was_closed; }

void Protocol::check_closed() {
    if (is_close()) {
        throw SocketClosed();
    }
}

// ----------------------------- SEND COMMANDS -----------------------------

void Protocol::send_Move(Move* move) {
    check_closed();
    send_uintEight(SEND_COMMAND_MOVE);
    send_uintEight(move->get_playerId());
    send_uintEight(move->get_dir());
}

void Protocol::send_MoveFaster(MoveFaster* moveFaster) {
    check_closed();
    send_uintEight(SEND_COMMAND_MOVE_FASTER);
    send_uintEight(moveFaster->get_playerId());
    send_uintEight(moveFaster->get_dir());
}

void Protocol::send_Jump(Jump* jump) {
    check_closed();
    send_uintEight(SEND_COMMAND_JUMP);
    send_uintEight(jump->get_playerId());
    send_uintEight(jump->get_dir());
}

void Protocol::send_Shoot(Shoot* shoot) {
    check_closed();
    send_uintEight(SEND_COMMAND_SHOOT);
    send_uintEight(shoot->get_playerId());
}


void Protocol::send_Match(MatchCommand* match) {
    check_closed();
    send_uintEight(SEND_COMMAND_MATCH);
    send_uintEight(match->getType());
    send_uintEight(match->get_number_players());
    send_string(match->get_match_name());
    send_string(match->get_map_name());
    send_uintEight(match->get_character_name());
}

void Protocol::send_Cheat(Cheats* cheat) {
    check_closed();
    send_uintEight(SEND_COMMAND_CHEAT);
    send_uintEight(cheat->get_playerId());
    send_uintEight(cheat->get_cheatID());
}

void Protocol::send_ChangeWeapon(ChangeWeapon* changeWeapon) {
    check_closed();
    send_uintEight(SEND_COMMAND_CHANGE_WEAPON);
    send_uintEight(changeWeapon->get_playerId());
}

void Protocol::send_SelectChampion(SelectChampion* selectChampion) {
    check_closed();
    send_uintEight(SEND_COMMAND_SELECT_CHAMPION);
    send_uintEight(selectChampion->get_playerId());
    send_uintEight(selectChampion->get_championType());
    send_string(selectChampion->get_match_name());
    send_string(selectChampion->get_map_name());
}

void Protocol::send_SpecialJazz(SpecialJazz* specialJazz) {
    check_closed();
    send_uintEight(SEND_COMMAND_JUMP_PUNCH_ATTACK_JAZZ);
    send_uintEight(specialJazz->get_playerId());
}

void Protocol::send_SpecialLori(SpecialLori* specialLori) {
    check_closed();
    send_uintEight(SEND_COMMAND_SHORT_RANGE_JUMP_KICK_LORI);
    send_uintEight(specialLori->get_playerId());
    send_uintEight(specialLori->get_dir());
}

void Protocol::send_SpecialSpaz(SpecialSpaz* specialSpaz) {
    check_closed();
    send_uintEight(SEND_COMMAND_SIDE_KICK_SPAZ);
    send_uintEight(specialSpaz->get_playerId());
    send_uintEight(specialSpaz->get_dir());
}

void Protocol::send_Command(Command* command) {
    switch (command->get_commandType()) {
        /*
        En cada caso se castea el comando a su tipo correspondiente y se envia.
        Hay que terminar cada caso con "break" para evitar el "fallthrough" no intencionado en el
        switch.
        */
        case COMMAND_CHEAT:
            send_Cheat(dynamic_cast<Cheats*>(command));
            break;
        case COMMAND_JUMP:
            send_Jump(dynamic_cast<Jump*>(command));
            break;
        case COMMAND_MOVE:
            send_Move(dynamic_cast<Move*>(command));
            break;
        case COMMAND_MOVE_FASTER:
            send_MoveFaster(dynamic_cast<MoveFaster*>(command));
            break;
        case COMMAND_SHOOT:
            send_Shoot(dynamic_cast<Shoot*>(command));
            break;
        case COMMAND_MATCH:
            send_Match(dynamic_cast<MatchCommand*>(command));
            break;
        case COMMAND_SELECT_CHAMPION:
            send_SelectChampion(dynamic_cast<SelectChampion*>(command));
            break;
        case COMMAND_CHANGE_WEAPON:
            send_ChangeWeapon(dynamic_cast<ChangeWeapon*>(command));
            break;
        case COMMAND_JUMP_PUNCH_ATTACK_JAZZ:
            send_SpecialJazz(dynamic_cast<SpecialJazz*>(command));
            break;
        case COMMANDS_SHORT_RANGE_JUMP_KICK_LORI:
            send_SpecialLori(dynamic_cast<SpecialLori*>(command));
            break;
        case COMMANDS_SIDE_KICK_SPAZ:
            send_SpecialSpaz(dynamic_cast<SpecialSpaz*>(command));
            break;
        default:
            break;
    }
}

// ----------------------------- RECEIVE COMMANDS -----------------------------

std::shared_ptr<Move> Protocol::receive_Move() {
    uint8_t player_id = receive_uintEight();
    uint8_t dir = receive_uintEight();
    return std::make_shared<Move>(player_id, dir);
}

std::shared_ptr<MoveFaster> Protocol::receive_MoveFaster() {
    uint8_t player_id = receive_uintEight();
    uint8_t dir = receive_uintEight();
    return std::make_shared<MoveFaster>(player_id, dir);
}

std::shared_ptr<Jump> Protocol::receive_Jump() {
    uint8_t player_id = receive_uintEight();
    uint8_t dir = receive_uintEight();
    return std::make_shared<Jump>(player_id, dir);
}

std::shared_ptr<Shoot> Protocol::receive_Shoot() {
    uint8_t player_id = receive_uintEight();
    return std::make_shared<Shoot>(player_id);
}

std::shared_ptr<MatchCommand> Protocol::receive_Match() {
    uint8_t type = receive_uintEight();
    uint8_t number_players = receive_uintEight();
    std::string match_name = receive_string();
    std::string map_name = receive_string();
    uint8_t character = receive_uintEight();
    ChampionType character_type = static_cast<ChampionType>(character);
    return std::make_shared<MatchCommand>(type, number_players, match_name, map_name,
                                          character_type);
}

std::shared_ptr<Cheats> Protocol::receive_Cheat() {
    uint8_t player_id = receive_uintEight();
    uint8_t cheat_id = receive_uintEight();
    return std::make_shared<Cheats>(player_id, cheat_id);
}

std::shared_ptr<ChangeWeapon> Protocol::receive_ChangeWeapon() {
    uint8_t player_id = receive_uintEight();
    return std::make_shared<ChangeWeapon>(player_id);
}

std::shared_ptr<SelectChampion> Protocol::receive_SelectChampion() {
    uint8_t player_id = receive_uintEight();
    ChampionType champion_type = static_cast<ChampionType>(receive_uintEight());
    std::string match_name = receive_string();
    std::string map_name = receive_string();
    return std::make_shared<SelectChampion>(player_id, champion_type, match_name, map_name);
}

std::shared_ptr<SpecialJazz> Protocol::receive_SpecialJazz() {
    uint8_t player_id = receive_uintEight();
    return std::make_shared<SpecialJazz>(player_id);
}

std::shared_ptr<SpecialLori> Protocol::receive_SpecialLori() {
    uint8_t player_id = receive_uintEight();
    uint8_t dir = receive_uintEight();
    return std::make_shared<SpecialLori>(player_id, dir);
}

std::shared_ptr<SpecialSpaz> Protocol::receive_SpecialSpaz() {
    uint8_t player_id = receive_uintEight();
    uint8_t dir = receive_uintEight();
    return std::make_shared<SpecialSpaz>(player_id, dir);
}

std::shared_ptr<Command> Protocol::receive_Command() {
    uint8_t command = receive_uintEight();
    switch (command) {
        case SEND_COMMAND_MOVE:
            return receive_Move();
        case SEND_COMMAND_MOVE_FASTER:
            return receive_MoveFaster();
        case SEND_COMMAND_JUMP:
            return receive_Jump();
        case SEND_COMMAND_SHOOT:
            return receive_Shoot();
        case SEND_COMMAND_MATCH:
            return receive_Match();
        case SEND_COMMAND_CHEAT:
            return receive_Cheat();
        case SEND_COMMAND_CHANGE_WEAPON:
            return receive_ChangeWeapon();
        case SEND_COMMAND_SELECT_CHAMPION:
            return receive_SelectChampion();
        case SEND_COMMAND_JUMP_PUNCH_ATTACK_JAZZ:
            return receive_SpecialJazz();
        case SEND_COMMAND_SHORT_RANGE_JUMP_KICK_LORI:
            return receive_SpecialLori();
        case SEND_COMMAND_SIDE_KICK_SPAZ:
            return receive_SpecialSpaz();
        default:
            throw InvalidCommand();
    }
}

// ----------------------------- SEND INFO -----------------------------

void Protocol::send_GameInfo(GameInfo* gameInfo) {
    check_closed();
    send_uintEight(SEND_GAME_INFO);
    std::map<std::string, std::string> matchesAvailable = gameInfo->getMatchesAvailable();
    send_uintEight(matchesAvailable.size());
    for (auto& match: matchesAvailable) {
        send_string(match.first);
        send_string(match.second);
    }
}

void Protocol::send_Info(Information* info) {
    check_closed();
    int type = info->get_infoType();
    if (type == SELECT_CHARACTER_INFO) {
        // sendDynamic(dynamic_cast<DynamicMap*>(info));
    } else if (type == GAME_INFO) {
        send_GameInfo(dynamic_cast<GameInfo*>(info));
    } else if (type == GAME_MAP_INFO) {
        // sendMap(dynamic_cast<Map*>(info));
    }
}

// ----------------------------- RECEIVE INFO -----------------------------

GameInfo* Protocol::receive_GameInfo() {
    check_closed();
    std::map<std::string, std::string> matches_available;
    int size_map = receive_uintEight();
    for (int i = 0; i < size_map; i++) {
        std::string matchName = receive_string();
        std::string mapName = receive_string();
        matches_available[matchName] = mapName;
    }
    return new GameInfo(matches_available);
}

std::shared_ptr<Information> Protocol::receive_Info() {
    check_closed();
    int type = receive_uintEight();
    if (type == SELECT_CHARACTER_INFO) {
        // return receiveDynamic();
    } else if (type == GAME_INFO) {
        return std::shared_ptr<Information>(receive_GameInfo());
    } else if (type == GAME_MAP_INFO) {
        // return receiveMap();
    }
    throw std::runtime_error("Invalid information");
}

// ----------------------------- SEND SNAPSHOTS -----------------------------

void Protocol::send_dimensions(const Snapshot& snapshot) {
    std::cout << "Sending dimensions" << std::endl;
    send_uintThirtyTwo(snapshot.map_dimensions.width);
    send_uintThirtyTwo(snapshot.map_dimensions.height);
    send_uintThirtyTwo(snapshot.map_dimensions.rabbit_amount);
    send_uintThirtyTwo(snapshot.map_dimensions.rabbit_width);
    send_uintThirtyTwo(snapshot.map_dimensions.rabbit_height);
}

void Protocol::send_rabbits(Snapshot& snapshot) {
    std::cout << "Sending rabbits" << std::endl;
    // enviar la cantidad de conejos
    send_uintEight(snapshot.rabbits.size());

    // enviar cada conejo
    for (auto& rabbit: snapshot.rabbits) {
        send_char(rabbit.id);
        send_uintThirtyTwo(rabbit.pos_x);
        send_uintThirtyTwo(rabbit.pos_y);
        send_uintThirtyTwo(rabbit.max_health);
        send_uintThirtyTwo(rabbit.health);
        send_char(rabbit.direction);
        send_uintThirtyTwo(rabbit.weapon);
        send_uintThirtyTwo(rabbit.state);
        send_uintThirtyTwo(rabbit.current_ammo);
    }
}

void Protocol::send_projectiles(Snapshot& snapshot) {
    std::cout << "Sending projectiles" << std::endl;
    // enviar la cantidad de proyectiles
    send_uintEight(snapshot.projectiles.size());
    // enviar cada proyectil
    for (auto& projectile: snapshot.projectiles) {
        // enviar cada atributo del proyectil
        send_uintEight(projectile.type);
        send_uintThirtyTwo(projectile.pos_x);
        send_uintThirtyTwo(projectile.pos_y);
        send_uintThirtyTwo(projectile.angle);
        send_uintThirtyTwo(projectile.direction);
        send_uintThirtyTwo(projectile.state);
        send_char(projectile.id);
        send_uintThirtyTwo(projectile.explosion_radius);
        send_uintThirtyTwo(projectile.radius);
        send_uintThirtyTwo(projectile.width);
        send_uintThirtyTwo(projectile.height);
    }
}

void Protocol::send_supplies(Snapshot& snapshot) {
    std::cout << "Sending supplies" << std::endl;
    // enviar la cantidad de suministros
    send_uintEight(snapshot.supplies.size());
    // enviar cada suministro
    for (auto& supply: snapshot.supplies) {
        send_uintEight(supply.type);
        send_uintThirtyTwo(supply.pos_x);
        send_uintThirtyTwo(supply.pos_y);
        send_char(supply.id);
        send_char(supply.state);
        send_uintThirtyTwo(supply.width);
        send_uintThirtyTwo(supply.height);
    }
}


void Protocol::send_Snapshot(Snapshot& snapshot) {
    send_dimensions(snapshot);
    send_rabbits(snapshot);
    send_projectiles(snapshot);
    send_supplies(snapshot);
}


// ----------------------------- RECEIVE SNAPSHOTS -----------------------------

void Protocol::receive_dimensions(Snapshot& snapshot) {
    std::cout << "Receiving dimensions" << std::endl;
    // recibir y setear las dimensiones del mapa en el snapshot pasado por referencia
    uint32_t width = receive_uintThirtyTwo();
    uint32_t height = receive_uintThirtyTwo();
    uint32_t rabbit_ammount = receive_uintThirtyTwo();
    uint32_t rabbit_width = receive_uintThirtyTwo();
    uint32_t rabbit_height = receive_uintThirtyTwo();
    snapshot.set_dimensions(width, height, rabbit_width, rabbit_height, rabbit_ammount);
}

void Protocol::receive_rabbits(Snapshot& snapshot) {
    std::cout << "Receiving rabbits" << std::endl;
    // recibir y setear rabbits en el snapshot pasado por referencia
    // recibir la cantidad de conejos
    uint8_t rabbit_amount = receive_uintEight();
    // recibir cada conejo
    for (int i = 0; i < rabbit_amount; i++) {
        // recibir cada atributo del conejo
        char id = receive_char();
        uint32_t pos_x = receive_uintThirtyTwo();
        uint32_t pos_y = receive_uintThirtyTwo();
        uint32_t max_health = receive_uintThirtyTwo();
        uint32_t health = receive_uintThirtyTwo();
        char direction = receive_char();
        uint32_t weapon = receive_uintThirtyTwo();
        uint32_t state = receive_uintThirtyTwo();
        uint32_t current_ammo = receive_uintThirtyTwo();
        // crear un RabbitSnapshot y agregarlo al vector de rabbits del snapshot
        RabbitSnapshot rabbit = RabbitSnapshot(id, pos_x, pos_y, max_health, health, direction,
                                               weapon, state, current_ammo);
        snapshot.rabbits.push_back(rabbit);
    }
}

void Protocol::receive_projectiles(Snapshot& snapshot) {
    std::cout << "Receiving projectiles" << std::endl;
    // recibir y setear projectiles en el snapshot pasado por referencia
    // recibir la cantidad de proyectiles
    uint8_t projectile_amount = receive_uintEight();
    // recibir cada proyectil
    for (int i = 0; i < projectile_amount; i++) {
        // recibir cada atributo del proyectil
        uint8_t type_receive = receive_uintEight();
        uint32_t pos_x = receive_uintThirtyTwo();
        uint32_t pos_y = receive_uintThirtyTwo();
        uint32_t angle = receive_uintThirtyTwo();
        uint32_t direction = receive_uintThirtyTwo();
        uint32_t state_receive = receive_uintThirtyTwo();
        char id = receive_char();
        uint32_t explosion_radius = receive_uintThirtyTwo();
        uint32_t radius = receive_uintThirtyTwo();
        uint32_t width = receive_uintThirtyTwo();
        uint32_t height = receive_uintThirtyTwo();
        // crear un ProjectileSnapshot y agregarlo al vector de projectiles del snapshot
        ProjectileSnapshot projectile =
                ProjectileSnapshot(type_receive, pos_x, pos_y, angle, direction, radius,
                                   state_receive, id, explosion_radius, width, height);
        snapshot.projectiles.push_back(projectile);
    }
}

void Protocol::receive_supplies(Snapshot& snapshot) {
    std::cout << "Receiving supplies" << std::endl;
    // recibir y setear supplies en el snapshot pasado por referencia
    // recibir la cantidad de suministros
    uint8_t supply_amount = receive_uintEight();
    // recibir cada suministro
    for (int i = 0; i < supply_amount; i++) {
        // recibir cada atributo del suministro
        uint8_t type_receive = receive_uintEight();
        SupplyType type = static_cast<SupplyType>(type_receive);
        uint32_t pos_x = receive_uintThirtyTwo();
        uint32_t pos_y = receive_uintThirtyTwo();
        char id = receive_char();
        char state_receive = receive_char();
        SupplyState state = static_cast<SupplyState>(state_receive);
        uint32_t width = receive_uintThirtyTwo();
        uint32_t height = receive_uintThirtyTwo();
        // crear un SupplySnapshot y agregarlo al vector de supplies del snapshot
        SupplySnapshot supply = SupplySnapshot(type, pos_x, pos_y, id, state, width, height);
        snapshot.supplies.push_back(supply);
    }
}

// Se recibe crea un Snapshot vacio y se le van agregando los elementos
Snapshot Protocol::receive_Snapshot() {
    Snapshot snapshot;
    receive_dimensions(snapshot);
    receive_rabbits(snapshot);
    receive_projectiles(snapshot);
    receive_supplies(snapshot);
    return snapshot;
}

Protocol::~Protocol() {
    this->was_closed = true;
    this->socket.~Socket();
}
