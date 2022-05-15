#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <string>
#include "chess.h"
#include <memory>
#include "observer.h"
#include "GraphicsDisplay.h"
#include "king.h"
#include "rook.h"
#include "chess.h"
#include "bishop.h"
#include "pawn.h"
#include "knight.h"
#include "queen.h"

class TextDisplay;
//class GraphicsDisplay;
class InvalidMove{};

struct Attack{
  std::shared_ptr<Chess> attacker;
  int attack_row;
  int attack_col;
};



class Grid {
  std::vector<std::vector<std::shared_ptr<Chess>>> theGrid;  // The actual grid.
  std::shared_ptr<Observer> td;
  std::shared_ptr<Observer> gd;
  std::vector<std::vector<int>> undo_list;
  bool enpassant = false;
  std::vector<std::shared_ptr<Chess>> ep_candidates;
  int ep_r;
  X ep_c;
  int ep_eat_r;
  X ep_eat_c;
   
  //std::vector<std::shared_ptr<Observer>> observers;

 public:
  void g_print_winner(char colour); 
  std::shared_ptr<Chess> get_ptr(int i, int j);
  std::vector<std::vector<int>> & getlist();
  bool undo();
  std::vector<std::vector<std::shared_ptr<Chess>>> getgrid();
  std::shared_ptr<Chess>& getpiece(X col, int row);
  void init(std::vector<std::vector<std::shared_ptr<Chess>>> & newGrid); // Sets up an 8 x 8 grid.  Clears old grid, if necessary.
  void setPiece(char type, X col, int row, char colour);
  void removePiece(X col, int row);
  bool isOccupy(X col, int row);
  bool is_block(X old_c, int old_y, X new_c, int new_y, char colour);
  void move(X old_x_cor, int old_y_cor, X x_cor, int y_cor, char colour);
  void computer1_move(std::shared_ptr<Chess> sour, std::vector<int> dest);
  void computer2_move(std::shared_ptr<Chess> sour, std::vector<int> dest);
  void computer3_move(char colour);
  void computer4_move(char colour);
  void addtd(std::shared_ptr<TextDisplay> td);
  bool castling(X old_c, int old_y, X new_c, int new_y, char colour);
  void castle_move(char colour, X new_c);
  void addgd(std::shared_ptr<GraphicsDisplay> gd);
  bool checkdone();
  void clear();
  bool hasvalidmove(X col, int row, char colour);
  bool ischeck(char colour);
  bool ischeckmate(char colour);
  bool isstalemate(char colour);
  void isenpassant(X old_c, int old_r, X new_c, int new_r);
  bool enpassant_move(X old_c, int old_r, X new_c, int new_r);
  void findvalidmove(std::shared_ptr<Chess> c, std::vector<std::vector<int>> & candidates);
  void search_best_move(std::shared_ptr<Chess> c, std::vector<std::vector<int>> & candidates, 
                            std::vector<Attack> & best_attacks, int & move_level);  
  void search_best_move3(std::shared_ptr<Chess> c, std::vector<std::vector<int>> & candidates, 
                            std::vector<Attack> & best_attacks, int & move_level, int & captured_level, int & is_captured_level);
  void remove_gd();
  bool check_captured(X col, int row, char colour);

	friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
