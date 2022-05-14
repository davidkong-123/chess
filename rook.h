#ifndef _ROOK_H_
#define _ROOK_H_
#include "chess.h"

class Rook: public Chess {
	  bool is_first;
	public:
	  Rook(char name, X x_cor, int y_cor, bool alive, char colour, bool is_first);
		bool valid(X x, int y) override;
    bool get_first();
    void set_first(bool first);
};

#endif
