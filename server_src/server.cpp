#include "server.h"


Server::Server(const char* servname):
        client_cmds_q(),
        sk_was_closed(false),
        list_of_q_msgs(),
        acceptor(servname, client_cmds_q, list_of_q_msgs),
        gameloop(client_cmds_q, list_of_q_msgs) {}


void Server::run() {
    acceptor.start();
    gameloop.start();
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "q") {
            sk_was_closed = true;
            acceptor.kill();
            gameloop.kill();
            acceptor.join();
            gameloop.join();
            break;
        }
    }
}
