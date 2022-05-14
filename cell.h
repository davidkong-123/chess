#ifndef CELL_H
#define CELL_H
#include <cstddef>
//#include "state.h"
#include "subject.h"
//#include "observer.h"
//#include "info.h"
#include "chess.h"
#include <string>

class Cell : public Subject {
  const X x_cor;
	const int y_cor;
	bool is_occupy;

	char colour;
	string name;

  // Add other private members if necessary

 public:
	bool get_occupy();
	X get_x();
	int get_y();
	char get_colour();
	string get_name();

	void erase(); // Changes if_occupied. 
  void setPiece(Chess chess);   // Place a piece of given colour here.

 // void notify(Subject<Info, State> &whoFrom) override;// My neighbours will call this
                                                // when they've changed state
  // Info getInfo() const override;
};
#endif
