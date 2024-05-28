#include "server_sender.h"

ServerSender::ServerSender(Protocol& protocolo, BroadcasterSnapshots& broadcaster_snapshots,
                           int player_id):
        protocolo(protocolo),
        broadcaster_snapshots(broadcaster_snapshots),
        keep_talking(true),
        is_alive(true),
        player_id(player_id) {}


void ServerSender::run() {
    while (keep_talking) {
        try {
            std::shared_ptr<Snapshot> game_snapshot =
                    this->broadcaster_snapshots.get_game(this->player_id);
            protocolo.send_Snapshot(*game_snapshot);
        } catch (const ClosedQueue& e) {
            // std::cerr << "Se cerró la queue" << std::endl;
            break;
        } catch (const std::exception& e) {
            std::cerr << "SENDER: No pude recibir comando o se cerro el cliente forzadamente"
                      << std::endl;
            break;
        }
    }
    broadcaster_snapshots.delete_player(this->player_id);
    this->is_alive = false;
}

bool ServerSender::is_dead() { return !this->is_alive; }

void ServerSender::kill() { this->keep_talking = false; }
