#ifndef POKER_H
#define POKER_H
#include <iostream>
#include <vector>

enum Suit { spade, heart, diamond, club };

class Poker {
 public:
  void showAttribute();
  void setSuit(Suit suit);
  void setNumber(std::string number);
  Poker(Suit, std::string);
  Poker();
  Suit getSuit();
  std::string getNumber();
  std::vector<std::string> getPattern();
  static void printPokers(std::vector<Poker> pokers);
  static void printPokers(Poker);
  void flipTheCard();

 private:
  Suit _suit;
  std::string _number;
  bool _isFaceUp;
  std::vector<std::string> _picture;
  std::vector<std::string> _backPattern;
  friend class Player;
};

#endif