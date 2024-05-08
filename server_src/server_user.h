#ifndef SERVERUSER_H
#define SERVERUSER_H
#include <list>
#include <string>
#include <utility>

#include "../common_src/common_socket.h"
#include "../common_src/protected_list_of_queues.h"
#include "../common_src/protocol.h"
#include "../common_src/queue.h"

#include "server_receiver.h"
#include "server_sender.h"

class ServerUser {
private:
    ServerProtocol protocol;
    ProtectedListOfQueues& list_of_q_msgs;
    ServerSender server_sender;
    Queue<uint8_t>& client_cmds_q;
    ServerReceiver server_receiver;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;

public:
    ServerUser(Socket&& peer, Queue<uint8_t>& client_cmds_q, ProtectedListOfQueues& list_of_q_msgs);
    void run();
    bool is_dead();
    void kill();
    ~ServerUser();
};

#endif
