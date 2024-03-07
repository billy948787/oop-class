#include "skin.h"

#include <iostream>

std::string Skin::getCharacterName() {
    return charaterName;
}

std::string Skin::getSkinName() {
    return skinName;
}

int Skin::getSkinPrice() {
    return skinPrice;
}

bool Skin::getStatus(){
    return status;
}

void Skin::setCharacterName(std::string name) {
    charaterName = name;
}

void Skin::setSkinName(std::string name) {
    skinName = name;
}

void Skin::setSkinPrice(int price) {
    skinPrice = price;
}

void Skin::setStatus(bool newStatus){
    status = newStatus;
}
