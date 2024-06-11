#ifndef SERVERRECIVER_H
#define SERVERRECIVER_H
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

#include "../common_src/container_protocol.h"
#include "../common_src/protocol.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

class ServerReceiver: public Thread {
private:
    Protocol& protocol;
    Queue<std::shared_ptr<Command>>& client_cmds_queue;
    bool& keep_talking;

public:
    ServerReceiver(Protocol& protocol, Queue<std::shared_ptr<Command>>& client_cmds_queue,
                   bool& keep_talking);

    virtual void run() override;
};

#endif
