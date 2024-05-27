#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "client_renderer.h"


class Client {
private:
    ClientRenderer renderer;

public:
    Client(const std::string& host, const std::string& service);

    void run(int argc, char* argv[]);

    //~Client();
};

#endif
