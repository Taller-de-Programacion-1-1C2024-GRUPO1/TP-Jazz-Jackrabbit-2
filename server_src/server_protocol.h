#include "../common_src/protocol.h"

class ServerProtocol: public Protocol {
public:
    using Protocol::Protocol;

    explicit ServerProtocol(Socket peer);

    // el server recibe un byte del cliente
    uint8_t get_byte();

    // envia un mensaje desde el server al cliente
    void send_server_enemy_status_count(const Message& msg);
};
