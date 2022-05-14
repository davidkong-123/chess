#include "bishop.h"
#include <cstdlib>

// ctor
Bishop::Bishop(char name, X x_cor, int y_cor, bool alive, char colour): Chess{name, x_cor, y_cor, alive, colour} {}



bool Bishop::valid(X x, int y) {
	if ((x == get_x()) && (y == get_y())) return false;
	if (abs(static_cast<int>(x) - static_cast<int>(get_x())) == 
		abs(static_cast<int>(y) - static_cast<int>(get_y()))) return true;
	return false;
}
