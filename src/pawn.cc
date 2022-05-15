#include "pawn.h"
#include <cstdlib>

// ctor
Pawn::Pawn(char name, X x_cor, int y_cor, bool alive, char colour, bool is_first): Chess{name, x_cor, y_cor, alive, colour}, is_first{is_first} {}


bool Pawn::get_first() {
  return is_first;
}


bool Pawn::valid(X x, int y) {
  X old_x = get_x();
  int old_y = get_y();
  int x_dist = static_cast<int>(x) - static_cast<int>(old_x);//get thedistance
  int y_dist = y - old_y;//get the distance
  
  char c = get_colour();
  if (c == 'B') {
      y_dist *= -1;
  } 
  
  if ((x_dist == 0) && (y_dist == 1)) {
   return true;
  } else if (is_first) {
    if ((x_dist == 0) && (y_dist == 2)) {
      return true;
    } else {
      return false;
    } 
  } else {
        return false;
    }
}

void Pawn::set_first(bool first){
    is_first = first;
}
  
