#ifndef _KNIGHT_
#define _KNIGHT_
#include "chess.h"

class Knight: public Chess {
   public:
	   Knight(char name, X x_cor, int y_cor, bool alive, char colour);
	   bool valid(X x, int y) override;
};

#endif
