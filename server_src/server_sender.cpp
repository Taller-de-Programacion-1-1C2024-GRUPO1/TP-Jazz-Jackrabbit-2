#include "server_sender.h"

ServerSender::ServerSender(Protocol& protocolo, BroadcasterSnapshots& broadcaster_snapshots,
                           bool& keep_talking, int player_id):
        protocolo(protocolo),
        broadcaster_snapshots(broadcaster_snapshots),
        keep_talking(keep_talking),
        player_id(player_id) {}


void ServerSender::run() {
    try {
        while (keep_talking) {
            std::shared_ptr<Snapshot> game_snapshot =
                    this->broadcaster_snapshots.get_game(this->player_id);
            protocolo.send_Snapshot(*game_snapshot);
        }
    } catch (const SocketClosed& e) {
        broadcaster_snapshots.delete_player(this->player_id);
        keep_talking = false;
    } catch (const ClosedQueue& e) {
        broadcaster_snapshots.delete_player(this->player_id);
        keep_talking = false;
    } catch (const std::exception& e) {
        broadcaster_snapshots.delete_player(this->player_id);
        keep_talking = false;
    }
}
