#ifndef SERVER_H
#define SERVER_H
#include <exception>
#include <iostream>
#include <list>
#include <string>

#include "../common_src/common_socket.h"
#include "../common_src/protected_list_of_queues.h"
#include "../common_src/protocol.h"
#include "../common_src/queue.h"

#include "server_acceptor.h"
#include "server_gameloop.h"
#include "server_user.h"

class Server {
private:
    Queue<uint8_t> client_cmds_q;
    bool sk_was_closed;
    ProtectedListOfQueues list_of_q_msgs;
    ServerAcceptor acceptor;
    GameLoop gameloop;

public:
    explicit Server(const char* servname);

    void run();
};

#endif
