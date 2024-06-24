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
#include "../game_src/qt_response.h"
#include "QT/client_lobby.h"

#include "client_drawer.h"
#include "client_map_editor.h"
#include "client_receiver.h"
#include "client_sender.h"
#include "new_map_info.h"


class Client {
private:
    Protocol protocol;
    Queue<std::unique_ptr<Command>> q_cmds;
    Queue<std::unique_ptr<QtResponse>> q_responses;
    int player_id;
    Queue<Snapshot> q_snapshots;
    ClientSender client_sender;
    ClientReceiver client_receiver;
    ClientDrawer drawer;
    NewMapInfo new_map_info;


public:
    Client(const std::string& host, const std::string& service);

    void run(int argc, char* argv[]);

    ~Client();
};

#endif
