#include "protocol.h"

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

void Protocol::send_user_created_match(int ACK_CREATED) {
    check_closed();
    send_uintEight(ACK_MATCH_CREATED_SUCCEED);
    send_uintEight(ACK_CREATED);
}

void Protocol::send_user_joined_match(int ACK_JOINED) {
    check_closed();
    send_uintEight(ACK_JOINED_SUCCEED);
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

int Protocol::receive_user_created_match() {
    check_closed();
    uint8_t ACK_CREATED = receive_uintEight();
    return ACK_CREATED;
}

int Protocol::receive_user_joined_match() {
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
            std::cout << "Cheat not implemented yet" << std::endl;
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
            std::cout << "Match not implemented yet" << std::endl;
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
        send_uintThirtyTwo(rabbit.angle);
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
        uint32_t angle = receive_uintThirtyTwo();
        uint32_t max_health = receive_uintThirtyTwo();
        uint32_t health = receive_uintThirtyTwo();
        char direction = receive_char();
        uint32_t weapon = receive_uintThirtyTwo();
        uint32_t state = receive_uintThirtyTwo();
        uint32_t current_ammo = receive_uintThirtyTwo();
        // crear un RabbitSnapshot y agregarlo al vector de rabbits del snapshot
        RabbitSnapshot rabbit = RabbitSnapshot(id, pos_x, pos_y, angle, max_health, health,
                                               direction, weapon, state, current_ammo);
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
