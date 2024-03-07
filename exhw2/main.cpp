#include <iostream>

#include "skin.h"

int main() {
    int userBalance;

    std::cout << "Enter your money:";
    std::cin >> userBalance;

    Skin Aa;
    Skin Ab;
    Skin Ba;
    Skin Bb;

    std::vector<Skin> allSkin;

    Aa.setCharacterName("A");
    Ab.setCharacterName("A");
    Ba.setCharacterName("B");
    Bb.setCharacterName("B");

    Aa.setSkinName("a");
    Ab.setSkinName("b");
    Ba.setSkinName("x");
    Bb.setSkinName("y");

    Aa.setSkinPrice(100);
    Ab.setSkinPrice(200);
    Ba.setSkinPrice(100);
    Bb.setSkinPrice(200);

    Aa.setStatus(false);
    Ab.setStatus(false);
    Ba.setStatus(false);
    Bb.setStatus(false);

    allSkin.push_back(Aa);
    allSkin.push_back(Ab);
    allSkin.push_back(Ba);
    allSkin.push_back(Bb);

    std::vector<Skin> a;
    std::vector<Skin> b;
    for (int i = 0; i < allSkin.size(); i++) {
        (allSkin[i].getCharacterName() == "A") ? a.push_back(allSkin[i]) : b.push_back(allSkin[i]);
    }
    while (true) {
        int action;
        std::string charater;
        std::string skin;

        std::cout << "Enter 1 to buy, 2 to leave: \n";

        std::cin >>
            action;

        if (action == 2) break;

        std::cout << "\nnow available:\n";

        std::cout << "\nA:\n  ";

        for (int i = 0; i < a.size(); i++) {
            std::cout << a[i].getSkinName() << ": " << ((!a[i].getStatus()) ? std::to_string(a[i].getSkinPrice()) : "sold out") << " ";
        }

        std::cout << "\n";
        std::cout << "B:\n  ";

        for (int i = 0; i < b.size(); i++) {
            std::cout << b[i].getSkinName() << ": " << ((!b[i].getStatus()) ? std::to_string(b[i].getSkinPrice()) : "sold out") << " ";
        }

        std::cout << "\n";

        std::cout << "your account balance : " << userBalance << "\n";

        std::cout << "Enter the charater you want to choose:\n";

        std::cin >> charater;

        if (charater != "A" && charater != "B") {
            std::cout << "Sorry you enter an not-existing charater\n";
            continue;
        }

        std::cout << "Enter a skin you want to purchase:";

        std::cin >> skin;

        if (charater == "A") {
            for (int i = 0; i < a.size(); i++) {
                if (skin == a[i].getSkinName() && (!a[i].getStatus())) {
                    if (userBalance - a[i].getSkinPrice() >= 0) {
                        userBalance -= a[i].getSkinPrice();
                        a[i].setStatus(true);
                        std::cout << "Purchase successful! Hope to see you again\n";
                        break;
                    } else {
                        std::cout << "Sorry! You don't have enough money\n";
                        break;
                    }
                } else if(i == a.size() - 1){
                    std::cout << "Sorry! There's something wrong. Please try again! \n";
                }
            }
        } else {
            for (int i = 0; i < b.size(); i++) {
                if (skin == b[i].getSkinName()) {
                    if (userBalance - b[i].getSkinPrice() >= 0) {
                        userBalance -= b[i].getSkinPrice();
                        b[i].setStatus(true);
                        std::cout << "Purchase successful! Hope to see you again\n";
                        break;
                    } else {
                        std::cout << "Sorry! You don't have enough money\n";
                        break;
                    }
                } else if (i == b.size() - 1) {
                    std::cout << "Sorry! There's something wrong. Please try again! \n";
                }
            }
        }
    }
}