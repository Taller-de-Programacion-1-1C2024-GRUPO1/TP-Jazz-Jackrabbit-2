#ifndef CLOCK_H
#define CLOCK_H

#include <chrono>
#include <cmath>
#include <functional>
#include <thread>

class Clock {
    int rate;
    std::function<void(int)> func;
    bool& keep_ticking;

public:
    Clock(std::function<void(int)> func, float frame_duration, bool& keep_ticking):
            func(func), keep_ticking(keep_ticking) {
        rate = std::round(frame_duration * 1000);
    }

    void tick() {
        int iter = 1;
        auto t1 = std::chrono::high_resolution_clock::now();
        // Loop principal, se ejecuta mientras keep_ticking sea true
        while (keep_ticking) {
            func(iter);
            iter = 0;
            auto t2 = std::chrono::high_resolution_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
            int rest = rate - diff;
            if (rest < 0) {
                int behind = (-1) * rest;
                rest = rate - behind % rate;
                int lost = behind + rest;
                t1 += std::chrono::milliseconds(lost);
                iter += lost / rate;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(rest));
            t1 += std::chrono::milliseconds(rate);
            iter++;
        }
    }

    void stop_ticking() { keep_ticking = false; }

    ~Clock() {}
};

#endif
