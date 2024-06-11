#ifndef SERVERSENDER_H
#define SERVERSENDER_H

#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

#include "../common_src/constants.h"
#include "../common_src/container_protocol.h"
#include "../common_src/protocol.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "broadcaster_snapshots.h"

class ServerSender: public Thread {
private:
    Protocol& protocolo;
    BroadcasterSnapshots& broadcaster_snapshots;
    bool& keep_talking;

    int player_id;

public:
    explicit ServerSender(Protocol& protocolo, BroadcasterSnapshots& broadcaster_snapshots,
                          bool& keep_talking, int player_id);
    virtual void run() override;
};

#endif
