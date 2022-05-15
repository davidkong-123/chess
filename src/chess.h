#ifndef _CHESS_H_
#define _CHESS_H_
#include <string>

enum class X {a=0, b, c, d, e, f, g, h};
class Chess {
      char name;
      X x_cor;
      int y_cor;
      bool alive;
	  char colour;
   public:
      Chess(char name, X x_cor, int y_cor, bool alive, char colour);
	  bool is_alive();
	  char get_colour();
      char get_name();
      X get_x();
      int get_y();
      virtual bool valid(X x, int y) = 0;
      void new_pos(X x, int y);
      void set_alive(bool a);
	  virtual ~Chess();
};

#endif
