#ifndef _KING_H_
#define _KING_H_
#include "chess.h"

class King: public Chess {
	  bool is_first;

	public: 
	  King(char name, X x_cor, int y_cor, bool alive, char colour, bool is_first);
	  bool get_first();
	  bool valid(X x, int y) override;
	  void set_first(bool first);
};

#endif
