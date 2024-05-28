#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "client_drawer.h"


class Client {
private:
    ClientDrawer drawer;

public:
    Client(const std::string& host, const std::string& service);

    void run(int argc, char* argv[]);

    //~Client();
};

#endif
