#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <iostream>
#include <list>
#include <mutex>
#include <string>

#include "../common_src/queue.h"
#include "../common_src/protected_list_of_queues.h"
#include "../common_src/constants.h"

class Broadcaster {
private:
    std::mutex mutex;
    ProtectedListOfQueues& list_of_q_msgs;

public:
    explicit Broadcaster(ProtectedListOfQueues& list_of_q_msgs);
    void broadcast(const Message msg);
    ~Broadcaster();
};

#endif