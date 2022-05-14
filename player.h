#ifndef _PLAY_
#define _PLAY_
#include <map>
#include <string>
#include <vector>
#include "chess.h"
#include "grid.h"
#include <memory>



class Player {
	char colour;
	int level;
	bool checkmate;
	Grid * grid;
	std::vector<std::shared_ptr<Chess>> mychess;
	std::vector<std::vector<int>> move_candidates;

		 
	 public:
	   Player(char colour, int level, bool checkmate, Grid * grid);
	   void addchess(std::shared_ptr<Chess> newchess);
	   void setlevel(int newlevel);
	   bool ischeck();
	   bool ischeckmate();
	   bool isWhite();
	   void human_makemove(X old_x_cor, int old_y_cor, X x_cor, int y_cor);
	   void comp_makemove();
	   void comp1_makemove();
	   void comp2_makemove();
	   void comp3_makemove();
	   int get_level();
	   
     
};





#endif
