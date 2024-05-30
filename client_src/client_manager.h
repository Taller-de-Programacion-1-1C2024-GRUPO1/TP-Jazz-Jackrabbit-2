#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "../common_src/common_socket.h"
#include "../common_src/constants.h"
#include "../common_src/protocol.h"
#include "../common_src/queue.h"

#include "client_receiver.h"
#include "client_sender.h"
#include "client_drawer.h"

class ClientManager {
private:
    Protocol protocol;
    Queue<Command*> q_cmds;
    Queue<Snapshot> q_snapshots;
    ClientDrawer client_drawer;
    ClientSender client_sender;
    Client_Receiver client_receiver;

public:
    ClientManager(const std::string& host, const std::string& service);

    void run();

    ~ClientManager();
};

#endif
