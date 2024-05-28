#include "server_acceptor.h"

ServerAcceptor::ServerAcceptor(const char* servname, int number_players,
                               const std::vector<std::string>& map_routes, bool* playing):
        sk(servname),
        sk_was_closed(false),
        number_players(number_players),
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

            /*
             * std::shared_ptr maneja automáticamente la memoria y garantiza
             * que el objeto se destruya cuando ya no haya referencias a él.
             * Si no usamos std::make_shared, podriamos terminar con un manejo manual de la memoria
             * que podría llevar a fugas de memoria (memory leaks) o acceso a memoria no válida
             * (use-after-free).
             */
            User* user = new User(std::make_shared<ContainerProtocol>(std::move(peer)),
                                  monitor_matches, playing);
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
