#ifndef CLIENTSENDER_H
#define CLIENTSENDER_H
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common_src/constants.h"
#include "../common_src/protocol.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "../game_src/commands/command_move.h"

class ClientSender: public Thread {
private:
    Protocol& protocol;
    Queue<std::unique_ptr<Command>>& q_cmds;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;

public:
    explicit ClientSender(Protocol& protocol, Queue<std::unique_ptr<Command>>& q_cmds);
    virtual void run() override;
    bool is_dead();
    void kill();
};


#endif
