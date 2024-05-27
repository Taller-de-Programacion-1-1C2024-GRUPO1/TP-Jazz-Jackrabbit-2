#ifndef CLIENT_H
#define CLIENT_H

#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "QT/client_lobby.h"
#include "client_renderer.h"



class Client {
private:
    //ClientLobby lobby;
    ClientRenderer renderer;

public:
    Client(const std::string& host, const std::string& service);

    void run(int argc, char* argv[]);

    //~Client();
};

#endif
