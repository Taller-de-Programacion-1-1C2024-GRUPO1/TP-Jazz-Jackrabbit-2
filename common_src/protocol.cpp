#include "protocol.h"

// Protocol
Protocol::Protocol(const std::string& host, const std::string& service):
        hostname(host), servname(service), socket(host.c_str(), service.c_str()) {}


Protocol::Protocol(Socket peer): socket(std::move(peer)), was_closed(false) {}

void Protocol::send_float(float num) {
    // convertimos el float ???
    check_closed();
}

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

float Protocol::receive_float() {
    // ni idea como trabajar el punto flotante
    check_closed();
    return 0.0;
}

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

void Protocol::send_char(char c) {
    socket.sendall(&c, sizeof(c), &was_closed);
    check_closed();
}

char Protocol::receive_char() {
    char c;
    socket.recvall(&c, sizeof(c), &was_closed);
    check_closed();
    return c;
}

bool Protocol::is_close() { return this->was_closed; }

void Protocol::check_closed() {
    if (is_close()) {
        throw SocketClosed();
    }
}

// -------------------------- SEND COMMANDS -----------------------------

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
    send_uintEight(shoot->get_dir());
}

/*
void Protocol::send_Match() {
    check_closed();
    send_uintEight(SEND_COMMAND_MATCH);
}

void Protocol::send_Cheat() {
    check_closed();
    send_uintEight(SEND_COMMAND_CHEAT);
}
*/

void Protocol::send_Command(Command* command) {
    switch (command->get_commandType()) {
        case COMMAND_CHEAT:
            // send_Cheat();
        case COMMAND_JUMP:
            send_Jump(dynamic_cast<Jump*>(command));
        case COMMAND_MOVE:
            send_Move(dynamic_cast<Move*>(command));
        case COMMAND_MOVE_FASTER:
            send_MoveFaster(dynamic_cast<MoveFaster*>(command));
        case COMMAND_SHOOT:
            send_Shoot(dynamic_cast<Shoot*>(command));
        case COMMAND_MATCH:
            // send_Match();
        default:
            break;
    }
}

// -------------------------- RECEIVE COMMANDS -----------------------------

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
    uint8_t dir = receive_uintEight();
    return std::make_shared<Shoot>(player_id, dir);
}

// std::shared_ptr<Match> Protocol::receive_Match() { return std::make_shared<Match>(); }

// std::shared_ptr<Cheats> Protocol::receive_Cheat() { return std::make_shared<Cheats>(); }

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
            // return receive_Match();
        case SEND_COMMAND_CHEAT:
            // return receive_Cheat();
        default:
            throw InvalidCommand();
    }
}

Protocol::~Protocol() {
    this->was_closed = true;
    this->socket.~Socket();
}
