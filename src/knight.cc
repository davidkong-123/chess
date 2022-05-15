#include "knight.h"
#include <cstdlib>

// ctor
Knight::Knight(char name, X x_cor, int y_cor, bool alive, char colour): Chess{name, x_cor, y_cor, alive, colour} {}


bool Knight::valid(X x, int y) {
  X old_x = get_x();
  int old_y = get_y();
  int x_dist = abs(static_cast<int>(x) - static_cast<int>(old_x));
  int y_dist = abs(y - old_y);
  if (x_dist == 0 && y_dist == 0) {
   return false;
  } else if ((x_dist == 2 && y_dist == 1) || (x_dist == 1 && y_dist == 2)) {
   return true;
  } else {
   return false;
  }
  
}
