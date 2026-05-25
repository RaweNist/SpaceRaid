#pragma once
#include <chrono>
#include <thread>
#include <functional>
class Timer {
private:
    std::thread thread;
    bool active;
public:
    Timer() : thread(), active(false) {}
    Timer(const Timer& copy);
    void start(int milliseconds, std::function<void()> callback);
    void stop();

    bool getActive() const;
    Timer& operator=(const Timer& t);
};