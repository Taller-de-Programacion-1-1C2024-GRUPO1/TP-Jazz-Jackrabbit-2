#ifndef CLIENTE_H
#define CLIENTE_H

#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "../common_src/common_socket.h"
#include "../common_src/protocol.h"
#include "../common_src/utils.h"

#include "client_drawer.h"
#include "client_listener.h"
#include "client_parser.h"


class Client {
private:
    ClientProtocol protocol;
    ClientListener listener;
    // ClientDrawer drawer;
    Parser parser;

    bool action_handler(std::pair<uint8_t, int> result);
    void read_handler(int num_msgs_to_read);

public:
    Client(const std::string& host, const std::string& service);

    // Lee de entrada estandar, procesa la linea, envia informacion al servidor y recibe e imprime
    // la respuesta
    void run();


    /////////////////////////////// IMPLEMENTAR ///////////////////////////////
    void reap_dead();
    void kill();
    void kill_all();
    /////////////////////////////// IMPLEMENTAR ///////////////////////////////


    ~Client();
};

#endif
