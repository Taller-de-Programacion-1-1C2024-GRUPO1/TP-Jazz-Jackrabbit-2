#include "server_sender.h"

ServerSender::ServerSender(ServerProtocol& protocol, ProtectedListOfQueues& list_of_q_msgs):
        protocol(protocol),
        q_msgs(),
        keep_talking(true),
        is_alive(true),
        list_of_q_msgs(list_of_q_msgs) {}


void ServerSender::run() {
    list_of_q_msgs.emplace_front(&q_msgs);

    while (keep_talking) {
        try {
            Message msg = q_msgs.pop();
            this->protocol.send_server_enemy_status_count(msg);
        } catch (const ClosedQueue& e) {
            // std::cerr << "Se cerró la queue" << std::endl;
            break;
        } catch (const std::exception& e) {
            std::cerr << "SENDER: No pude recibir comando o se cerro el cliente forzadamente"
                      << std::endl;
            break;
        }
    }
    list_of_q_msgs.remove(&q_msgs);
    this->is_alive = false;
}


bool ServerSender::is_dead() { return !this->is_alive; }


void ServerSender::kill() {
    this->keep_talking = false;
    q_msgs.close();
}
