#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "client_manager.h"

class Client {
private:
    ClientManager manager;

public:
    Client(const std::string& host, const std::string& service);

    void run(int argc, char* argv[]);

    //~Client();
};

#endif
