#include "client_renderer.h"

ClientRenderer::ClientRenderer(const std::string& host, const std::string& service):
        manager(std::move(host), std::move(service)) {}


void ClientRenderer::run() {
    // SDL2pp
    std::cout << "ClientRenderer::run()\n";
    manager.run();
    std::cout << "ClientRenderer finished end\n";
}
