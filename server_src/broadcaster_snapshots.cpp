#include "broadcaster_snapshots.h"

BroadcasterSnapshots::BroadcasterSnapshots() {}

void BroadcasterSnapshots::add_player(int id, Queue<std::shared_ptr<Snapshot>>* playerQueue) {
    players_queues[id] = playerQueue;
}

void BroadcasterSnapshots::broadcast(std::shared_ptr<Snapshot> game) {
    std::lock_guard<std::mutex> lock(m);
    for (auto& player_queue: players_queues) {
        try {
            player_queue.second->push(game);
        } catch (const ClosedQueue& err) {
            /*
             * Si el jugador ya no esta conectado, no se envia el snapshot
             * y se continua con el siguiente jugador.
             * Esto se hace para evitar que el servidor se bloquee.
             * El jugador desconectado sera eliminado cuando
             * se libere el lock de la funcion.
             */
            continue;
        }
    }
}

std::shared_ptr<Snapshot> BroadcasterSnapshots::get_game(int id) {
    return players_queues[id]->pop();
}

void BroadcasterSnapshots::delete_player(int id) {
    std::lock_guard<std::mutex> lock(m);
    players_queues.erase(id);
}

bool BroadcasterSnapshots::is_empty() { return players_queues.size() == 0; }
