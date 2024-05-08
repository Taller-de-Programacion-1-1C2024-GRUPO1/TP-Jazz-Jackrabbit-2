#include "server_acceptor.h"


ServerAcceptor::ServerAcceptor(const char* servname, Queue<uint8_t>& client_cmds_q,
                               ProtectedListOfQueues& list_of_q_msgs):
        sk(servname),
        sk_was_closed(false),
        client_cmds_q(client_cmds_q),
        list_of_q_msgs(list_of_q_msgs),
        server_users(),
        is_alive(true),
        keep_talking(true) {}


void ServerAcceptor::run() {
    while (keep_talking && !sk_was_closed) {
        try {
            Socket peer = sk.accept();
            ServerUser* th = new ServerUser(std::move(peer), client_cmds_q, list_of_q_msgs);
            th->run();
            reap_dead();
            server_users.push_back(th);
        } catch (const std::exception& e) {
            // std::cerr << "Error en el accept" << std::endl;
            break;
        }
    }
    kill_all();
}


void ServerAcceptor::reap_dead() {
    server_users.remove_if([](ServerUser* u) {
        if (u->is_dead()) {
            delete u;
            return true;
        }
        return false;
    });
}


void ServerAcceptor::kill_all() {
    for (auto& c: server_users) {
        c->kill();
        delete c;
    }
    server_users.clear();
}


void ServerAcceptor::kill() {
    sk.~Socket();
    this->keep_talking = false;
    this->sk_was_closed = true;
}
