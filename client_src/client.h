#ifndef CLIENTE_H
#define CLIENTE_H

#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "../common_src/common_socket.h"
#include "../common_src/constants.h"
#include "../common_src/protocol.h"

#include "client_parser.h"
#include "client_receiver.h"
#include "client_sender.h"


class Client {
private:
    Protocol protocol;
    Parser parser;
    Queue<Command> q_cmds;
    Queue<Snapshot> q_snapshots;
    ClientSender client_sender;
    Client_Receiver client_receiver;

    bool action_handler(std::pair<uint8_t, int> result);
    void read_handler(int num_msgs_to_read);

public:
    Client(const std::string& host, const std::string& service);

    // Lee de entrada estandar, procesa la linea, envia informacion al servidor y recibe e imprime
    // la respuesta
    void run();

    ~Client();
};

#endif
