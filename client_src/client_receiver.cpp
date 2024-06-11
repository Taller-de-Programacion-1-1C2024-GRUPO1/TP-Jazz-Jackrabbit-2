#include "client_receiver.h"

#include <chrono>

ClientReceiver::ClientReceiver(Protocol& protocol, Queue<std::unique_ptr<QtResponse>>& q_responses,
                               Queue<Snapshot>& q_snapshots, int& player_id):
        protocol(protocol),
        q_responses(q_responses),
        q_snapshots(q_snapshots),
        keep_talking(true),
        is_alive(true),
        player_id(player_id) {}


void ClientReceiver::run() {
    bool game_started = false;
    while (keep_talking) {
        try {
            if (!game_started) {
                std::unique_ptr<QtResponse> response = this->protocol.receive_qt_response();
                std::cout << "RESPONSE: info type: " << response->get_info_type()
                          << "response: " << response->get_response()
                          << "matches_available().size: "
                          << response->get_matches_available().size() << std::endl;
                if (response->get_response() > 0) {
                    player_id = response->get_response();
                    game_started = true;
                }


                q_responses.push(std::move(response));

            } else {
                std::cout << "Recibiendo Snapshot" << std::endl;
                Snapshot snap = this->protocol.receive_Snapshot();
                q_snapshots.push(snap);
            }


        } catch (const ClosedQueue& e) {
            // HACER EL CORRECTO MANEJO DE ERRORES
            std::cerr << "Se cerró la Snapshot queue" << std::endl;
            break;
        } catch (const SocketClosed& e) {
            std::cerr << "Se cerro el socket (Receiver)" << std::endl;
            break;
        } catch (const std::exception& e) {
            std::cerr << "Client Receiver: error al recibir snapshot " << std::endl;
            break;
        }
    }
    q_responses.close();
    q_snapshots.close();
    this->is_alive = false;
}


bool ClientReceiver::is_dead() { return !this->is_alive; }


void ClientReceiver::kill() {
    this->keep_talking = false;
}
