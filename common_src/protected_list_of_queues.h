#ifndef PROTECTED_LIST_H
#define PROTECTED_LIST_H
#include <iostream>
#include <list>
#include <mutex>
#include <thread>

#include "queue.h"


class ProtectedListOfQueues {
private:
    std::list<Queue<uint16_t>*> list;
    std::mutex mutex;

public:
    void emplace_front(Queue<uint16_t>* cola) {
        std::lock_guard<std::mutex> lock(mutex);
        list.push_back(cola);
    }

    void remove(Queue<uint16_t>* cola) {
        std::lock_guard<std::mutex> lock(mutex);
        list.remove(cola);
    }

    typename std::list<Queue<uint16_t>*>::iterator begin() { return list.begin(); }

    typename std::list<Queue<uint16_t>*>::iterator end() { return list.end(); }
};

#endif
