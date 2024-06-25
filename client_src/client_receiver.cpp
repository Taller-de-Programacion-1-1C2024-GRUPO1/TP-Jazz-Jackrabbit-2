#include "client_receiver.h"


ClientReceiver::ClientReceiver(Protocol& protocol, Queue<std::unique_ptr<QtResponse>>& q_responses,
                               Queue<Snapshot>& q_snapshots, int& player_id,
                               Queue<std::unique_ptr<Command>>& q_cmds):
        protocol(protocol),
        q_responses(q_responses),
        q_snapshots(q_snapshots),
        keep_talking(true),
        is_alive(true),
        player_id(player_id),
        q_cmds(q_cmds) {}


void ClientReceiver::run() {
    bool game_started = false;
    while (keep_talking) {
        try {
            if (!game_started) {
                std::unique_ptr<QtResponse> response = this->protocol.receive_qt_response();
                int response_type = response->get_response();
                if (response_type > 0 && response_type < ERROR_PROT) {
                    player_id = response_type;
                    game_started = true;
                }
                q_responses.push(std::move(response));
            } else {
                Snapshot snap = this->protocol.receive_Snapshot();
                q_snapshots.push(snap);
            }
        } catch (const ClosedQueue& e) {
            // std::cerr << "Client Receiver: Snapshot queue or Responses queue closed" <<
            // std::endl;
            break;
        } catch (const SocketClosed& e) {
            // std::cerr << "Client Receiver: The socket was closed" << std::endl;
            break;
        } catch (const std::exception& e) {
            // std::cerr << "Client Receiver: error receiving snapshot or response" << std::endl;
            break;
        }
    }
    q_responses.close();
    q_snapshots.close();
    q_cmds.close();
    this->is_alive = false;
}


bool ClientReceiver::is_dead() { return !this->is_alive; }


void ClientReceiver::kill() { this->keep_talking = false; }
