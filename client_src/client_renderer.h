#ifndef CLIENTRENDERER_H
#define CLIENTRENDERER_H

#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "client_manager.h"


class ClientRenderer {
private:
    ClientManager manager;


public:
    ClientRenderer(const std::string& host, const std::string& service);

    void run();

    //~ClientRenderer();
};

#endif