#ifndef _PAWN_
#define _PAWN_
#include "chess.h"
#include <string>

class Pawn: public Chess {
    bool is_first;
  public:
    Pawn(char name, X x_cor, int y_cor, bool alive, char colour, bool is_first);
		bool get_first();
    bool valid(X x, int y) override;
    void set_first(bool first);
};

#endif
