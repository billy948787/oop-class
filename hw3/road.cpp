#include "road.h"

Road::Road(int row, int column) : Object(row, column, true, '-') {}

Type Road::getType() { return Type::roadType; }
