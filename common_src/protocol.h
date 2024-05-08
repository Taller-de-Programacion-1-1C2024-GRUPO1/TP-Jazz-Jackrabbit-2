#ifndef COMMON_PROTOCOLO_H
#define COMMON_PROTOCOLO_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "../common_src/utils.h"

#include "common_socket.h"


class Protocol {
protected:
    const std::string hostname;
    const std::string servname;
    Socket socket;
    bool was_closed = false;

public:
    // Constructor para el cliente
    Protocol(const std::string& host, const std::string& service);

    // Constructor para el server
    explicit Protocol(Socket peer);
    bool is_close();
    ~Protocol();
};


class ClientProtocol: public Protocol {
public:
    using Protocol::Protocol;

    ClientProtocol(const std::string& host, const std::string& service);

    // envia un byte desde el cliente al server
    bool send_byte(uint8_t& msg);

    // el cliente recibe desde el server
    void get_msg(Message& msg);
};


class ServerProtocol: public Protocol {
public:
    using Protocol::Protocol;

    explicit ServerProtocol(Socket peer);

    // el server recibe un byte del cliente
    uint8_t get_byte();

    // envia un mensaje desde el server al cliente
    void send_server_enemy_status_count(const Message& msg);
};


#endif
