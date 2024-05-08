#ifndef SERVERSENDER_H
#define SERVERSENDER_H
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common_src/protected_list_of_queues.h"
#include "../common_src/protocol.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "../common_src/utils.h"


class ServerSender: public Thread {
private:
    ServerProtocol& protocol;
    Queue<uint16_t> q_msgs;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;
    ProtectedListOfQueues& list_of_q_msgs;

public:
    explicit ServerSender(ServerProtocol& protocol, ProtectedListOfQueues& list_of_q_msgs);
    virtual void run() override;
    bool is_dead();
    void kill();
};


#endif
