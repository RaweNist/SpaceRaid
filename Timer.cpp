#include "Timer.h"
#include <thread>

Timer::Timer(const Timer& copy)
{
    active = copy.active;
}

void Timer::start(int milliseconds, std::function<void()> callback)
{
    // Если таймер уже работает, останавливаем его
    stop();

    active = true;
    thread = std::thread([=]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
        if (active) {
            callback(); // вызываем функцию по таймеру
            stop();
        }
        });
    thread.detach(); // отделяем поток, чтобы он работал независимо
}

void Timer::stop()
{
    active = false;
}

bool Timer::getActive() const
{
    return active;
}

Timer& Timer::operator=(const Timer& t)
{
    return *this;
}
