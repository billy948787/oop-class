#include <iostream>

#include "poker.h"

int main() {
    std::string number;
    int columns;
    int inputSuit;
    Suit suit;
    std::vector<Poker> pokers;

    std::cout << "請輸入花色(0 : 黑桃, 1 : 愛心, 2 : 方塊, 3 : 梅花)";
    std::cin >> inputSuit;

    std::cout << "一行要印幾張撲克牌";
    std::cin >> columns;

    switch (inputSuit) {
        case 0:
            suit = spade;
            break;
        case 1:
            suit = heart;
            break;
        case 2:
            suit = diamond;
            break;
        case 3:
            suit = club;
            break;
    }

    for (int i = 1; i <= 13; i++) {
        Poker poker;
        switch (i) {
            case 1:
                poker.setNumber("A");
                break;
            case 11:
                poker.setNumber("J");
                break;
            case 12:
                poker.setNumber("Q");
                break;
            case 13:
                poker.setNumber("K");
                break;
            default:
                poker.setNumber(std::to_string(i));
        }
        poker.setSuit(suit);
        pokers.push_back(poker);
    }

    for (int i = 0; i < (13 / columns) + 1; i++) {
        int index = i * columns;
        for (int j = 0; j < pokers[0].getPattern().size(); j++) {
            for (int k = index; k < index + columns; k++) {
                if (k > 12)
                    break;
                std::cout << pokers[k].getPattern()[j] << " ";
            }
            std::cout << "\n";
        }
    }
}