#include "wall.h"

Wall::Wall(int row, int column) : Object(row, column, false, '/'){};

Type Wall::getType() { return Type::wallType; }