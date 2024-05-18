#ifndef PROTECTED_LIST_H
#define PROTECTED_LIST_H
#include <iostream>
#include <list>
#include <mutex>
#include <thread>

#include "queue.h"
#include "constants.h"

class ProtectedListOfQueues {
private:
    std::list<Queue<Message>*> list;
    std::mutex mutex;

public:
    void emplace_front(Queue<Message>* cola) {
        std::lock_guard<std::mutex> lock(mutex);
        list.push_back(cola);
    }

    void remove(Queue<Message>* cola) {
        std::lock_guard<std::mutex> lock(mutex);
        list.remove(cola);
    }

    typename std::list<Queue<Message>*>::iterator begin() { return list.begin(); }

    typename std::list<Queue<Message>*>::iterator end() { return list.end(); }
};

#endif
