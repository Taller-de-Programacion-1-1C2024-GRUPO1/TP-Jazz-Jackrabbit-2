#ifndef SERVERRECIVER_H
#define SERVERRECIVER_H
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "../common_src/protocol.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"


class ServerReceiver: public Thread {
private:
    ServerProtocol& protocol;
    Queue<uint8_t>& client_cmds_q;
    std::atomic<bool> keep_talking;  // habla sobre el estado del socket
    std::atomic<bool> is_alive;      // habla sobre el estado del thread


public:
    ServerReceiver(ServerProtocol& protocol, Queue<uint8_t>& client_cmds_q);

    virtual void run() override;
    bool is_dead();
    void kill();

    ~ServerReceiver();
};

#endif
