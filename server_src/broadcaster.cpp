#include "broadcaster.h"

Broadcaster::Broadcaster(ProtectedListOfQueues& list_of_q_msgs):
        mutex(), list_of_q_msgs(list_of_q_msgs) {}

void Broadcaster::broadcast(const Message msg) {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& q: list_of_q_msgs) {
        try {
            bool could_push;
            could_push = q->try_push(msg);
        } catch (const std::exception& e) {
            std::cerr << "Error en el push del broadcaster" << std::endl;
        }
    }
    return;
}

Broadcaster::~Broadcaster() {}
