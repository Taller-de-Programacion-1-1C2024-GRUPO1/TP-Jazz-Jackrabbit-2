#ifndef SERVERACCEPTOR_H
#define SERVERACCEPTOR_H
#include <iostream>
#include <list>
#include <sstream>
#include <unordered_map>
#include <utility>

#include "../common_src/protected_list_of_queues.h"
#include "../common_src/thread.h"

#include "server_user.h"


class ServerAcceptor: public Thread {

private:
    Socket sk;
    bool sk_was_closed;
    Queue<uint8_t>& client_cmds_q;
    ProtectedListOfQueues& list_of_q_msgs;
    std::list<ServerUser*> server_users;
    std::atomic<bool> is_alive;
    std::atomic<bool> keep_talking;

public:
    explicit ServerAcceptor(const char* servname, Queue<uint8_t>& client_cmds_q,
                            ProtectedListOfQueues& list_of_q_msgs);
    virtual void run() override;
    void reap_dead();
    void kill();
    void kill_all();
};
#endif
