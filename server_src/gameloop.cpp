#include "gameloop.h"

#define EXTRA_HEALTH ConfigSingleton::getInstance().get_extra_health()

Gameloop::Gameloop(Queue<std::shared_ptr<Command>>& client_cmd_queue,
                   BroadcasterSnapshots& broadcaster_snapshots, std::list<Player*>& players,
                   Map& map, bool* playing):
        client_cmd_queue(client_cmd_queue),
        broadcaster_snapshots(broadcaster_snapshots),
        players(players),
        map(map),
        playing(playing),
        game_ended(false) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

void Gameloop::send_initial_snapshots() {

    // Se debe leer el mapa elegido por el usuario y crearlo
    std::shared_ptr<Snapshot> snapshot = map.get_init_snapshot();

    // Enviar el snapshot inicial
    push_all_players(*snapshot);
}

void Gameloop::push_all_players(const Snapshot& snapshot) {
    // Enviar a cada jugador la snapshot
    for (auto& player: players) {
        Queue<std::shared_ptr<Snapshot>>& player_snapshot_queue = player->get_snapshots_queue();
        try {
            player_snapshot_queue.push(std::make_shared<Snapshot>(snapshot));
        } catch (const ClosedQueue& err) {
            continue;
        }
    }
}

void Gameloop::run() {
    try {
        std::shared_ptr<Command> game_command;
        while (client_cmd_queue.try_pop(game_command)) {
            game_command->execute_Command();
        }


    } catch (ClosedQueue& err) {}
}

void Gameloop::stop() { *playing = false; }
