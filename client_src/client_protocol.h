#include "../common_src/protocol.h"

class ClientProtocol: public Protocol {
public:
    using Protocol::Protocol;

    ClientProtocol(const std::string& host, const std::string& service);

    // envia un byte desde el cliente al server
    bool send_byte(uint8_t& msg);

    // el cliente recibe desde el server
    void get_msg(Message& msg);
};
