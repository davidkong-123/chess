#include "rook.h"

// ctor
Rook::Rook(char name, X x_cor, int y_cor, bool alive, char colour, bool is_first): Chess{name, x_cor, y_cor, alive, colour}, is_first{is_first} {}


bool Rook::get_first(){
  return is_first;
}


bool Rook::valid(X x, int y) {
	if ((x == get_x()) && (y == get_y())) return false;
	if ((x == get_x()) || (y == get_y())) return true;
	return false;
}

void Rook::set_first(bool first){
    is_first = first;
}

