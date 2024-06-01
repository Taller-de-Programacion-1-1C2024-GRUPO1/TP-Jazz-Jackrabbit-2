#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "../common_src/common_socket.h"
#include "../common_src/constants.h"
#include "../common_src/protocol.h"
#include "../common_src/queue.h"
#include "../common_src/snapshots/snapshot.h"
#include "../game_src/commands/command.h"
#include "QT/client_lobby.h"

#include "client_drawer.h"
#include "client_receiver.h"
#include "client_sender.h"


class Client {
private:
    Protocol protocol;
    Queue<Command*> q_cmds;
    Queue<Snapshot> q_snapshots;
    ClientSender client_sender;
    Client_Receiver client_receiver;
    // ClientLobby lobby;
    ClientDrawer drawer;


public:
    Client(const std::string& host, const std::string& service);


    void run(int argc, char* argv[]);

    ~Client();
};

#endif
