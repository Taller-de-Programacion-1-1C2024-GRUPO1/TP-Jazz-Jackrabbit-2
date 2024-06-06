#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>
#include <fstream>
#include <memory>  // Para std::shared_ptr
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

//#include "client_config.h"


class Client {
private:
    Protocol protocol;
    std::shared_ptr<Queue<std::shared_ptr<Command>>> q_cmds;  // Cambiado a std::shared_ptr
    std::shared_ptr<Queue<int>> q_responses;                  // Cambiado a std::shared_ptr
    std::atomic<bool> game_started;
    int player_id;
    Queue<Snapshot> q_snapshots;
    ClientSender client_sender;
    ClientReceiver client_receiver;
    // ClientLobby lobby;
    ClientDrawer drawer;


public:
    Client(const std::string& host, const std::string& service);


    void run(int argc, char* argv[]);

    ~Client();
};

#endif
