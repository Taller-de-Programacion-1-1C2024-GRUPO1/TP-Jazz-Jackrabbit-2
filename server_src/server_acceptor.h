#ifndef SERVERACCEPTOR_H
#define SERVERACCEPTOR_H

#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../common_src/thread.h"

#include "monitor_matches.h"
#include "server_users.h"

class ServerAcceptor: public Thread {

private:
    Socket sk;
    bool sk_was_closed;

    int id_counter;
    std::list<User*> server_users;

    std::string map_routes;

    std::atomic<bool> is_alive;
    bool& server_running;

public:
    explicit ServerAcceptor(const char* servname, const std::string& map_routes,
                            bool& server_running);
    virtual void run() override;
    void stop() override;
    void reap_dead();
    void kill_all();
};

#endif
