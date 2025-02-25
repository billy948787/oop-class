#include "operation_controller.h"

std::map<std::string, bool> OperationController::doubleOrSurrender(int point) {
  return operation->doubleOrSurrender(point);
}

bool OperationController::hit(std::vector<Poker> cards,
                              std::vector<Poker> bankerCards) {
  return operation->hit(cards, bankerCards);
}

bool OperationController::insurance() { return operation->insurance(); }

int OperationController::stake(int money) { return operation->stake(money); }

OperationController::OperationController(Operation& operation)
    : operation(&operation) {}

void OperationController::changeOperation(Operation& operation) {
  this->operation = &operation;
}