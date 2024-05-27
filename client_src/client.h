#ifndef CLIENT_H
#define CLIENT_H

#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "client_lobby.h"
#include "client_renderer.h"


class Client {
private:
    ClientLobby lobby;
    ClientRenderer renderer;

public:
    Client(const std::string& host, const std::string& service);

    void run();

    //~Client();
};

#endif
