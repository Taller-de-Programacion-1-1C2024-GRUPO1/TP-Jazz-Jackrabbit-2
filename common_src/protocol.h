#ifndef COMMON_PROTOCOLO_H
#define COMMON_PROTOCOLO_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "../common_src/constants.h"

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

#endif
