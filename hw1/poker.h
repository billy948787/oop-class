#ifndef _POKER_H_
#define _POKER_H_
#include <iostream>
#include <vector>

enum Suit {
    spade,
    heart,
    diamond,
    club
};

class Poker {
   public:
    void showAttribute();
    void setSuit(Suit suit);
    void setNumber(std::string number);
    Suit getSuit();
    std::string getNumber();
    std::vector<std::string> getPattern();

   private:
    Suit _suit;
    std::string _number;
    std::vector<std::string>
        _picture;
};

#endif