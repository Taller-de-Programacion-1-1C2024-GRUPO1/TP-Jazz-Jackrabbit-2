#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <utility>

#include "../common_src/protocol.h"

class ServerProtocol: public Protocol {
public:
    explicit ServerProtocol(Socket peer);

    // el server recibe un byte del cliente
    uint8_t get_byte();

    // envia un mensaje desde el server al cliente
    void send_server_enemy_status_count(const Message& msg);
};

#endif
