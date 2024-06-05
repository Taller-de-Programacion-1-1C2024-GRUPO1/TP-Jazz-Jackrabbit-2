#include "client_receiver.h"

#include <chrono>

ClientReceiver::ClientReceiver(Protocol& protocol, Queue<int>& q_responses,
                               std::atomic<bool>& game_started, Queue<Snapshot>& q_snapshots):
        protocol(protocol),
        q_responses(q_responses),
        game_started(game_started),
        q_snapshots(q_snapshots),
        keep_talking(true),
        is_alive(true) {}


void ClientReceiver::run() {
    while (keep_talking) {
        try {
            if (!game_started) {
                int response = this->protocol.receive_response();
                std::cout << "pusheando respuesta: " << response << "\n";
                q_responses.push(response);
            } else {
                //Snapshot snap = this->protocol.receive_Snapshot();
                //std::cout << "Client Receiver: Recibiendo Snapshot" << std::endl;
                //q_snapshots.push(snap);
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        } catch (const ClosedQueue& e) {
            std::cerr << "Se cerró la Snapshot queue" << std::endl;
            break;
        } catch (const std::exception& e) {
            std::cerr << "Client Receiver: error al recibir snapshot o se cerro el servidor "
                         "forzadamente"
                      << std::endl;
            break;
        }
    }
    this->is_alive = false;
}


bool ClientReceiver::is_dead() { return !this->is_alive; }


void ClientReceiver::kill() {
    this->keep_talking = false;
    q_snapshots.close();
}
