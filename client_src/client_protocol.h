#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>

#include "../common_src/protocol.h"

class ClientProtocol: public Protocol {
public:
    ClientProtocol(const std::string& host, const std::string& service);

    // envia un byte desde el cliente al server
    bool send_byte(uint8_t& msg);

    // el cliente recibe desde el server
    void get_msg(Message& msg);
};

#endif
