#include "server_acceptor.h"

ServerAcceptor::ServerAcceptor(const char* servname, int number_players,
                               const std::string& map_routes, bool* playing):
        sk(servname),
        sk_was_closed(false),
        number_players(number_players),
        id_counter(0),
        server_users(),
        map_routes(map_routes),
        is_alive(true),
        keep_talking(true),
        playing(playing) {}

void ServerAcceptor::run() {
    MonitorMatches monitor_matches(map_routes);

    while (keep_talking && !sk_was_closed) {
        try {
            Socket peer = sk.accept();
            // se podría hacer un unique_ptr
            User* user = new User(id_counter, std::make_shared<ContainerProtocol>(std::move(peer)),
                                  monitor_matches, playing);
            this->id_counter++;
            user->run();
            reap_dead();
            server_users.push_back(user);
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

void ServerAcceptor::kill() {
    sk.~Socket();
    this->keep_talking = false;
    this->sk_was_closed = true;
}

void ServerAcceptor::stop() {
    sk.shutdown(SHUT_RDWR);
    sk.close();
    kill_all();
}
