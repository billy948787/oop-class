#include "poker.h"

#include <iostream>

Poker::Poker(std::string suit, std::string number) {
    Poker::suit = suit;
    Poker::number = number;
}

void Poker::showAttribute() {
    std::cout << Poker::suit << '\n'
              << Poker::number;
}