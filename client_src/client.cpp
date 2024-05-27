#include "client.h"

Client::Client(const std::string& host, const std::string& service):
        lobby(),
        renderer(std::move(host), std::move(service)) {}

void Client::run() {
    lobby.run();
    renderer.run();
}



