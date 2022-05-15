#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "chess.h"

class Queen: public Chess {
	public:
	  Queen(char name, X x_cor, int y_cor, bool alive, char colour);
		bool valid(X x, int y) override;
};

#endif
