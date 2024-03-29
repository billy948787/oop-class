#include "time.h"
#include <iostream>

void Time::setTime(int h, int m, int s) {
    if (h > 23 || m > 59 || s > 59 || h < 0 || m < 0 || s < 0) {
        std::cout << "Invalid time" << std::endl;
        return;
    } else {
        hour = h;
        minute = m;
        second = s;
    }
}

void Time::setTime(int s) {
    if (s > 86400 || s < 0) {
        std::cout << "Invalid time" << std::endl;
        return;
    } else {
        hour = s / 3600;
        s = s % 3600;
        minute = s / 60;
        second = s % 60;
    }
}

Time::Time() {
    hour = 0;
    minute = 0;
    second = 0;
}

void Time::showTime() {
    if (hour > 12) {
        std::cout << (hour - 12 > 10 ? std::to_string(hour - 12) : "0" + std::to_string(hour - 12)) << ":"
                  << (minute > 10 ? std::to_string(minute) : "0" + std::to_string(minute)) << ":"
                  << (second > 10 ? std::to_string(second) : "0" + std::to_string(second)) << " PM" << "\n";
    } else {
        std::cout << (hour > 10 ? std::to_string(hour) : "0" + std::to_string(hour)) << ":"
                  << (minute > 10 ? std::to_string(minute) : "0" + std::to_string(minute)) << ":"
                  << (second > 10 ? std::to_string(second) : "0" + std::to_string(second)) << " AM" << "\n";
    }
}