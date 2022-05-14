#include "chess.h"

Chess::~Chess(){}

Chess::Chess(char name, X x_cor, int y_cor, bool alive, char colour): name{name}, x_cor{x_cor}, y_cor{y_cor}, alive{alive}, colour{colour} {}

char Chess::get_colour() {
	return colour;
}
bool Chess::is_alive() {
   return alive;
}
char Chess::get_name() {
   return name;
}
X Chess::get_x() {
   return x_cor;
}
int Chess::get_y() {
   return y_cor;
}
void Chess::new_pos(X x, int y) {
   x_cor = x;
   y_cor = y;
}
void Chess::set_alive(bool a) {
   alive = a;
}
