#include "client_receiver.h"

#include <chrono>

Client_Receiver::Client_Receiver(ClientProtocol& protocol, Queue<Snapshot>& q_snapshots):
        protocol(protocol), q_snapshots(q_snapshots), keep_talking(true), is_alive(true) {}


void Client_Receiver::run() {
    while (keep_talking) {
        try {
            // Snapshot snap;
            // this->protocol.recive(snap);
            // q_snapshots.push(snap);

            std::cout << "Client Receiver: Recibiendo Snapshot" << std::endl;
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


bool Client_Receiver::is_dead() { return !this->is_alive; }


void Client_Receiver::kill() {
    this->keep_talking = false;
    q_snapshots.close();
}
