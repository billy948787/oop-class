#include "poker.h"

#include <iostream>
#include <vector>

void Poker::showAttribute() {
    std::cout << _suit << " "
              << _number << "\n";
}

Suit Poker::getSuit() {
    return _suit;
}

std::string Poker::getNumber() {
    return _number;
}

std::vector<std::string> Poker::getPattern() {
    return _picture;
}

void Poker::setNumber(std::string number) {
    _number = number;
}

void Poker::setSuit(Suit suit) {
    _suit = suit;
    switch (_suit) {
        case spade:
            _picture.push_back("-----------");
            (_number == "10") ? _picture.push_back("|10       |") : _picture.push_back("|" + _number + "        |");
            _picture.push_back("|    *    |");
            _picture.push_back("|   ***   |");
            _picture.push_back("|  *****  |");
            _picture.push_back("| ******* |");
            _picture.push_back("|*********|");
            _picture.push_back("| ******* |");
            _picture.push_back("|  * * *  |");
            _picture.push_back("|   ***   |");
            _picture.push_back("|  *****  |");
            _picture.push_back("|  *****  |");
            (_number == "10") ? _picture.push_back("|       10|") : _picture.push_back("|        " + _number + "|");
            _picture.push_back("-----------");
            break;
        case heart:
            break;
        case diamond:
            break;
        case club:
            break;
    }
}