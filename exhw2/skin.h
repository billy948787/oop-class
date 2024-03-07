#ifndef _SKIN_H_
#define _SKIN_H_
#include <iostream>

class Skin {
   public:
    std::string getCharacterName();
    std::string getSkinName();
    int getSkinPrice();
    bool getStatus();

    void setCharacterName(std::string);
    void setSkinName(std::string);
    void setSkinPrice(int);
    void setStatus(bool);

   private:
    std::string charaterName;
    std::string skinName;
    int skinPrice;
    bool status;
};

#endif