#ifndef _POKER_H_
#define _POKER_H_
#include <iostream>

class Poker {
   public:
    void show();
    void showAttribute(); 
    Poker(std::string, std::string);

   private:
    std::string suit;
    std::string number;
};

#endif