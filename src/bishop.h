#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "chess.h"

class Bishop: public Chess {
	public:
 	  Bishop(char name, X x_cor, int y_cor, bool alive, char colour); 
		bool valid(X x, int y) override;
};

#endif
