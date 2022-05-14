#include "king.h"

// ctor
King::King(char name, X x_cor, int y_cor, bool alive, char colour, bool is_first): Chess{name, x_cor, y_cor, alive, colour}, is_first{is_first} {}

bool King::get_first() {
	return is_first;
}

bool King::valid(X x, int y) {
	if ((x == get_x()) && (y == get_y())) return false;
	if ((abs(static_cast<int>(x) - static_cast<int>(get_x())) < 2) &&
		abs(static_cast<int>(y) - static_cast<int>(get_y())) < 2) return true;
	return false;
}

void King::set_first(bool first){
    is_first = first;
}
