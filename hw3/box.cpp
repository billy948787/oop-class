#include "box.h"

Box::Box(int row, int column) : Object(row, column, true, '1') {}

Type Box::getType() { return Type::boxType; }