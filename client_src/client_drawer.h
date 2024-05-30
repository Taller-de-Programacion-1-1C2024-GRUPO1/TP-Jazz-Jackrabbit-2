#ifndef CLIENT_DRAWER_H
#define CLIENT_DRAWER_H

// pre-commit run --hook-stage manual --all-files

#include "../common_src/queue.h"
#include "../common_src/snapshots/snapshot.h"
#include "../game_src/commands/command.h"
#include "../client_src/client_shifting_drawable.h"

class ClientDrawer {
private:
    std::vector<ShiftingDrawable*> rabbits;
    std::vector<ShiftingDrawable*> supplies;
    std::vector<ShiftingDrawable*> projectiles;
    std::vector<ShiftingDrawable*> enemies;

    Queue<Command*> &q_cmds;
    Queue<Snapshot> &q_snapshots;
    int client_id;

public:
    ClientDrawer(Queue <Command*> &q_cmds, Queue <Snapshot> &q_snapshots);
    void handle_keyboard(bool &game_running);
    void process_snapshot();

    int run();

    //~ClientDrawer();
};

#endif
