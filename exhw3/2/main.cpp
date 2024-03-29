#include <iostream>
#include <vector>

#include "time.h"

int main() {
    Time time;
    std::cout << "Initial time is 00:00:00 AM\n";
    std::string input;
    std::vector<std::string> inputs;

    while (true) {
        inputs.clear();
        std::cout << "Please enter a time in the format HH MM SS or SS:";
        do {
            std::cin >> input;
            if (input == "-1") {
                return 0;
            }

            inputs.push_back(input);
        } while (getchar() != '\n');

        if (inputs.size() == 3) {
            time.setTime(std::stoi(inputs[0]), std::stoi(inputs[1]), std::stoi(inputs[2]));
        } else if (inputs.size() == 1) {
            time.setTime(std::stoi(inputs[0]));
        } else {
            std::cout << "Invalid input" << std::endl;
            return 0;
        }

        time.showTime();
    }
}