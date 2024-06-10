#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>
#include <fstream>
#include <memory>
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
#include "client_map_editor.h"
#include "client_receiver.h"
#include "client_sender.h"
//#include "client_config.h"


class Client {
private:
    Protocol protocol;
    Queue<std::unique_ptr<Command>> q_cmds;
    Queue<int> q_responses;
    int player_id;
    Queue<Snapshot> q_snapshots;  /////////// SI el snapshot no es demasiado grande (200bytes)
                                  ///(copia) esta bien asi, sino hacerlo en el heap (2kbytes)
    ClientSender client_sender;
    ClientReceiver client_receiver;
    ClientDrawer drawer;


    // el editor NO TIENE QUE COMUNICArse con el sertver
    // HACER para el martes un manual de usuario como instalar, jugar, etc..

public:
    Client(const std::string& host, const std::string& service);


    void run(int argc, char* argv[]);

    ~Client();
};

#endif
