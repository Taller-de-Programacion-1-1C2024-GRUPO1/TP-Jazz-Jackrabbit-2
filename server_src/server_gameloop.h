#ifndef GAMELOOP_H
#define GAMELOOP_H
#include <algorithm>
#include <chrono>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <unordered_map>

#include "../common_src/constants.h"
#include "../common_src/protected_list_of_queues.h"
#include "../common_src/protocol.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "broadcaster.h"
#include "enemy.h"


class GameLoop: public Thread {
private:
    Queue<uint8_t>& client_cmds_q;
    Enemies enemies;
    std::atomic<bool> is_alive;
    std::atomic<bool> keep_talking;
    Broadcaster broadcaster;

public:
    explicit GameLoop(Queue<uint8_t>& client_cmds_q, ProtectedListOfQueues& list_of_q_msgs);
    virtual void run() override;
    void kill();
    void gameloop_push_msg(const Message& msg);
};


#endif
