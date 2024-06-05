#ifndef CLIENTRECEIVER_H
#define CLIENTRECEIVER_H
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common_src/constants.h"
#include "../common_src/protocol.h"
#include "../common_src/queue.h"
#include "../common_src/snapshots/snapshot.h"
#include "../common_src/thread.h"

class ClientReceiver: public Thread {
private:
    Protocol& protocol;
    std::shared_ptr<Queue<int>> q_responses; // Cambiado a std::shared_ptr
    std::atomic<bool>& game_started;
    Queue<Snapshot>& q_snapshots;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;

public:
    explicit ClientReceiver(Protocol& protocol, std::shared_ptr<Queue<int>> q_responses,
                            std::atomic<bool>& game_started, Queue<Snapshot>& q_snapshots);
    virtual void run() override;
    bool is_dead();
    void kill();
};


#endif
