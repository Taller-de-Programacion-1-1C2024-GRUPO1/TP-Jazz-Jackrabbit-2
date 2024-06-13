#ifndef CLIENTRECEIVER_H
#define CLIENTRECEIVER_H
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../common_src/constants.h"
#include "../common_src/protocol.h"
#include "../common_src/queue.h"
#include "../common_src/snapshots/snapshot.h"
#include "../common_src/thread.h"
#include "../game_src/qt_response.h"

class ClientReceiver: public Thread {
private:
    Protocol& protocol;
    Queue<std::unique_ptr<QtResponse>>& q_responses;
    Queue<Snapshot>& q_snapshots;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;
    int& player_id;
    Queue<std::unique_ptr<Command>>& q_cmds;

public:
    explicit ClientReceiver(Protocol& protocol, Queue<std::unique_ptr<QtResponse>>& q_responses,
                            Queue<Snapshot>& q_snapshots, int& player_id,
                            Queue<std::unique_ptr<Command>>& q_cmds);
    virtual void run() override;
    bool is_dead();
    void kill();
};


#endif
