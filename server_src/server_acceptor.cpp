#include "server_acceptor.h"

ServerAcceptor::ServerAcceptor(const char* servname, const std::string& map_routes,
                               bool& server_running):
        sk(servname),
        sk_was_closed(false),
        id_counter(INITIAL_ID),
        server_users(),
        map_routes(map_routes),
        is_alive(true),
        server_running(server_running) {}

void ServerAcceptor::run() {
    MonitorMatches monitor_matches(map_routes);
    while (server_running) {
        try {
            Socket peer = sk.accept();
            User* user = new User(id_counter, std::make_shared<ContainerProtocol>(std::move(peer)),
                                  monitor_matches, this->server_running);
            std::cout << "New user connected!" << std::endl;
            this->id_counter++;
            user->start();
            server_users.push_back(user);
            reap_dead();
        } catch (const std::exception& e) {
            monitor_matches.close_matches();
            break;
        }
    }
}

void ServerAcceptor::reap_dead() {
    server_users.remove_if([](User* u) {
        if (!u->is_alive()) {
            u->join();
            delete u;
            return true;
        }
        return false;
    });
}

void ServerAcceptor::kill_all() {
    for (auto& c: server_users) {
        if (c->is_alive()) {
            c->kill();
        }
        c->join();
        delete c;
    }
    server_users.clear();
}

void ServerAcceptor::stop() {
    server_running = false;
    sk.shutdown(SHUT_RDWR);
    sk.close();
    kill_all();
}
