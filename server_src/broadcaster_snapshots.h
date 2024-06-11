#ifndef BROADCASTER_SNAPSHOTS_H
#define BROADCASTER_SNAPSHOTS_H

#include <iostream>
#include <map>
#include <memory>

#include "../common_src/queue.h"
#include "../common_src/snapshots/snapshot.h"

class BroadcasterSnapshots {

private:
    std::mutex m;
    std::map<int, Queue<std::shared_ptr<Snapshot>>*> players_queues;

public:
    BroadcasterSnapshots();

    void add_player(int id, Queue<std::shared_ptr<Snapshot>>* player_queue);
    void broadcast(std::shared_ptr<Snapshot> game);
    void delete_player(int id);
    bool is_empty();
    std::shared_ptr<Snapshot> get_game(int id);
};

#endif
