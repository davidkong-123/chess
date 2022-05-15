#include "grid.h"
#include "textdisplay.h"
#include "GraphicsDisplay.h" 
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include <memory>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <random>


void Grid::remove_gd(){
    this->gd.reset();
}

void Grid::g_print_winner(char colour) {
    std::static_pointer_cast<GraphicsDisplay>(gd)->print_winner(colour);
}

// Get Grid. 
std::vector<std::vector<std::shared_ptr<Chess>>> Grid::getgrid() {
    return theGrid;
}

std::shared_ptr<Chess> Grid::get_ptr(int i, int j) {
    return theGrid.at(i).at(j);
}

// GetList.
std::vector<std::vector<int>> & Grid::getlist() {
    return undo_list;
}

// Undo. 
bool Grid::undo(){
    
    if (undo_list.size() < 2) {
        std::cout << "Cannot undo." << std::endl;
        return false;
    }
    
    std::vector<int> last = undo_list[undo_list.size() - 1];
    std::vector<int> second_last = undo_list[undo_list.size() - 2];
    undo_list.pop_back();
    undo_list.pop_back();
    
    X old_col = static_cast<X>(last[0]);
    int old_row = last[1];
    X new_col = static_cast<X>(last[2]);
    int new_row = last[3];
    
    char type;
    char c;
    
    if (last.size() > 4) {
        if (last[5] == 0) {
            c = 'W';
            if (last[4] == 1) {
                type = 'Q';
            } else if (last[4] == 2) {
                type = 'R';
            } else if (last[4] == 3) {
                type = 'B';
            } else if (last[4] == 4) {
                type = 'N';
            } else {
                type = 'P';
            }
        } else {
            c = 'B';
            if (last[4] == 1) {
                type = 'q';
            } else if (last[4] == 2) {
                type = 'r';
            } else if (last[4] == 3) {
                type = 'b';
            } else if (last[4] == 4) {
                type = 'n';
            } else {
                type = 'p';
            }
        }
    }
    
    char place_type = theGrid.at(new_row).at(static_cast<int>(new_col))->get_name();
    char place_colour;
    if (isupper(place_type)) {
        place_colour = 'W';
    } else {
        place_colour = 'B';
    }
    
    removePiece(new_col, 8-new_row);
    setPiece(place_type, old_col, 8-old_row, place_colour);
    
    if (last.size() > 4) setPiece(type, new_col, 8 - new_row, c);
    
    // Checks for second last move. 
    X oldc = static_cast<X>(second_last[0]);
    int oldr = second_last[1];
    X new_c = static_cast<X>(second_last[2]);
    int new_r = second_last[3];
    
    char type1;
    char c1;
    
    if (second_last.size() > 4) {
        if (second_last[5] == 0) {
            c1 = 'W';
            if (second_last[4] == 1) {
                type1 = 'Q';
            } else if (second_last[4] == 2) {
                type1 = 'R';
            } else if (second_last[4] == 3) {
                type1 = 'B';
            } else if (second_last[4] == 4) {
                type1 = 'N';
            } else {
                type1 = 'P';
            }
        } else {
            c1 = 'B';
            if (second_last[4] == 1) {
                type1 = 'q';
            } else if (second_last[4] == 2) {
                type1 = 'r';
            } else if (second_last[4] == 3) {
                type1 = 'b';
            } else if (second_last[4] == 4) {
                type1 = 'n';
            } else {
                type1 = 'p';
            }
        }
    }
    
    char place_type1 = theGrid.at(new_r).at(static_cast<int>(new_c))->get_name();
    char place_colour1;
    if (isupper(place_type1)) {
        place_colour1 = 'W';
    } else {
        place_colour1 = 'B';
    }
    
    removePiece(new_c, 8-new_r);
    setPiece(place_type1, oldc, 8-oldr, place_colour1);
    
    if (second_last.size() > 4) setPiece(type1, new_c, 8 - new_r, c1);
    return true;
}

// has validmove
bool Grid::hasvalidmove(X col, int row, char colour){
    for (int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            // check nullptr
            if (theGrid.at(i).at(j) != nullptr){
                
                // check colour
                if (theGrid.at(i).at(j)->get_colour() != colour){
                    
                    // check pawn attack
                    char type = theGrid.at(row).at(static_cast<int>(col))->get_name();
                    if (colour == 'W' && type == 'P' && (row == i + 1) && (static_cast<int>(col) == j - 1 ||
                        static_cast<int>(col) == j + 1)){ // black attack white
                        
                        // check is check
                        theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                   
                        std::shared_ptr<Chess> temp = theGrid.at(row).at(static_cast<int>(col));
                        theGrid.at(row).at(static_cast<int>(col)).reset();
                        theGrid.at(row).at(static_cast<int>(col)) = nullptr;            
                            
                            
                        bool check1 = ischeck('W');  
                        if (!check1){
                            theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                            theGrid.at(i).at(j) = temp;
                            temp.reset();
                            return true;
                        }
                        theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                        theGrid.at(i).at(j) = temp;
                        temp.reset();
                        
                        
                    } else if (colour == 'B' && type == 'p' && (row == i - 1) && (static_cast<int>(col) == j - 1 ||
                      static_cast<int>(col) == j + 1)) { // white attack black
                          
                        // check is check
                        theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                   
                        std::shared_ptr<Chess> temp = theGrid.at(row).at(static_cast<int>(col));
                        theGrid.at(row).at(static_cast<int>(col)).reset();
                        theGrid.at(row).at(static_cast<int>(col)) = nullptr;            
                            
                            
                        bool check2 = ischeck('B');  
                        if (!check2){
                            theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                            theGrid.at(i).at(j) = temp;
                            temp.reset();
                            return true;
                        }
                        theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                        theGrid.at(i).at(j) = temp;
                        temp.reset();
                        
                    } else if (colour == 'W' && type == 'P' ){
                        continue;
                    } else if (colour == 'B' && type == 'p') {
                        continue;
                    } 
                    
                    // check valid move
                    bool valid1 = theGrid.at(row).at(static_cast<int>(col))->valid(static_cast<X>(j), 8 - i);
                    
                    if (valid1){
                        bool block1 = is_block(col, row, static_cast<X>(j), i,  colour);
                        if (!block1){
                            
                            // check is check
                            theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                   
                            std::shared_ptr<Chess> temp = theGrid.at(row).at(static_cast<int>(col));
                            theGrid.at(row).at(static_cast<int>(col)).reset();
                            theGrid.at(row).at(static_cast<int>(col)) = nullptr;            
                            
                            if (colour == 'W'){
                              bool check3 = ischeck('W');
                              if (!check3){
                                theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                                theGrid.at(i).at(j) = temp;
                                temp.reset();
                                return true;
                              }
                              
                            } else {
                              bool check4 = ischeck('B');  
                              if (!check4){
                                theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                                theGrid.at(i).at(j) = temp;
                                temp.reset();
                                return true;
                              }
                            }
                            theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                            theGrid.at(i).at(j) = temp;
                            temp.reset();
                                  
                        }
                    }
                    
                    
                    
                    
                } else {
                   continue;    
                }
            } else { // nullptr
            
                // check enpassant
                if (enpassant == true){
                   if (ep_c == static_cast<X>(j) && ep_r == i){
                        for(size_t i = 0; i < ep_candidates.size(); ++i){
                             if (theGrid.at(row).at(static_cast<int>(col)) == ep_candidates.at(i)){
                                 
                                // check
                                std::shared_ptr<Chess> temp1 = theGrid.at(ep_eat_r).at(static_cast<int>(ep_eat_c));
                                theGrid.at(ep_eat_r).at(static_cast<int>(ep_eat_c)).reset();
                                theGrid.at(ep_eat_r).at(static_cast<int>(ep_eat_c)) = nullptr;
                                
                                // swap
                                theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                                
                                std::shared_ptr<Chess> temp2 = theGrid.at(row).at(static_cast<int>(col));
                                theGrid.at(row).at(static_cast<int>(col)).reset();
                			    theGrid.at(row).at(static_cast<int>(col)) = nullptr;
                                
                                bool check5 = ischeck(colour);
                                if (!check5){
                                    
                                    // swap back
                                    theGrid.at(ep_eat_r).at(static_cast<int>(ep_eat_c)) = temp1;
                                    
                                    theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                                    theGrid.at(i).at(j) = temp2;
                                    temp1.reset();
                                    temp2.reset();
                                    return true;
                                }
                             }
                        }
                   }
                }
                
                
                    // check castling
                    bool castle = castling(col, row, static_cast<X>(j), i, colour);
                    if (castle){
                        castle_move(colour, static_cast<X>(j));
                        if (colour == 'W'){
                            bool check6 = ischeck('W');
                            
                            if (check6 == false) {
                                if (static_cast<X>(j) == X::g || static_cast<X>(j) == X::f) { //bot right
                                    theGrid.at(7).at(static_cast<int>(4)).swap(theGrid.at(7).at(static_cast<int>(6)));
                                    theGrid.at(7).at(static_cast<int>(4))->new_pos(X::e, 1);
                                    theGrid.at(7).at(static_cast<int>(5)).swap(theGrid.at(7).at(static_cast<int>(7)));
                                    theGrid.at(7).at(static_cast<int>(7))->new_pos(X::h, 1);
                                    return true;
                                } else {//left bot
                                    theGrid.at(7).at(0).swap(theGrid.at(7).at(3));
                                    theGrid.at(7).at(0)->new_pos(X::a, 1);
                                    theGrid.at(7).at(2).swap(theGrid.at(7).at(4));
                                    theGrid.at(7).at(4)->new_pos(X::e, 1);
                                    return true;
                                }
                            }
                            
                             if (static_cast<X>(j) == X::g || static_cast<X>(j) == X::f) { //bot right
                                theGrid.at(7).at(static_cast<int>(4)).swap(theGrid.at(7).at(static_cast<int>(6)));
                                theGrid.at(7).at(static_cast<int>(4))->new_pos(X::e, 1);
                                theGrid.at(7).at(static_cast<int>(5)).swap(theGrid.at(7).at(static_cast<int>(7)));
                                theGrid.at(7).at(static_cast<int>(7))->new_pos(X::h, 1);
    
                            } else {//left bot
                                theGrid.at(7).at(0).swap(theGrid.at(7).at(3));
                                theGrid.at(7).at(0)->new_pos(X::a, 1);
                                theGrid.at(7).at(2).swap(theGrid.at(7).at(4));
                                theGrid.at(7).at(4)->new_pos(X::e, 1);
                                return true;
                            }
                            
                            
                        } else {
                            bool check7 = ischeck('B');
                                     
                            if (check7 == false) {
                                if (static_cast<X>(j) == X::g || static_cast<X>(j) == X::f) { //top right
                                    theGrid.at(0).at(static_cast<int>(4)).swap(theGrid.at(0).at(static_cast<int>(6)));
                                    theGrid.at(0).at(static_cast<int>(4))->new_pos(X::e, 8);
                                    theGrid.at(0).at(static_cast<int>(5)).swap(theGrid.at(0).at(static_cast<int>(7)));
                                    theGrid.at(0).at(static_cast<int>(7))->new_pos(X::h, 8);
                                    return true;
                                } else {
                                    theGrid.at(0).at(0).swap(theGrid.at(0).at(3));
                                    theGrid.at(0).at(0)->new_pos(X::a, 8);
                                    theGrid.at(0).at(2).swap(theGrid.at(0).at(4));
                                    theGrid.at(0).at(4)->new_pos(X::e, 8);
                                    return true;
                                }
                            }
                            
                            if (static_cast<X>(j) == X::g || static_cast<X>(j) == X::f) { //top right
                                theGrid.at(0).at(static_cast<int>(4)).swap(theGrid.at(0).at(static_cast<int>(6)));
                                theGrid.at(0).at(static_cast<int>(4))->new_pos(X::e, 8);
                                theGrid.at(0).at(static_cast<int>(5)).swap(theGrid.at(0).at(static_cast<int>(7)));
                                theGrid.at(0).at(static_cast<int>(7))->new_pos(X::h, 8);
                            } else {
                                theGrid.at(0).at(0).swap(theGrid.at(0).at(3));
                                theGrid.at(0).at(0)->new_pos(X::a, 8);
                                theGrid.at(0).at(2).swap(theGrid.at(0).at(4));
                                theGrid.at(0).at(4)->new_pos(X::e, 8);
                            }
                            
                            
                        }
                        
                    }    else {
                    
                    
                        // check valid move
                        bool valid2 = theGrid.at(row).at(static_cast<int>(col))->valid(static_cast<X>(j), 8 - i);
                            
                            if (valid2){
                                bool block2 = is_block(col, row, static_cast<X>(j), i, colour);
                                if (!block2){
                                    
                                     // check enpassant
                                    isenpassant(col, row, static_cast<X>(j), i);
                                    
                                    if (enpassant){
                                        enpassant = false;
                                        continue;
                                    }
                                    
                                    
                                    // check pawn move
                                    if(theGrid.at(row).at(static_cast<int>(col))->get_name() == 'P' || theGrid.at(row).at(static_cast<int>(col))->get_name() == 'p'){
                                        if (std::static_pointer_cast<Pawn>(theGrid.at(row).at(static_cast<int>(col)))->get_first() == false && abs(row -i) == 2){
                                            continue;
                                        }
                                        
                                    }
                                    
                                    // check is check
                                    theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                           
                                    std::shared_ptr<Chess> temp = theGrid.at(row).at(static_cast<int>(col));
                                    theGrid.at(row).at(static_cast<int>(col)).reset();
                                    theGrid.at(row).at(static_cast<int>(col)) = nullptr;            
                                    
                                    if (colour == 'W'){
                                      bool check3 = ischeck('W');
                                      if (!check3){
                                        theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                                        theGrid.at(i).at(j) = temp;
                                        temp.reset();
                                        return true;
                                      } 
                                      
                                    } else {
                                      bool check4 = ischeck('B');  
                                      if (!check4){
                                        theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                                        theGrid.at(i).at(j) = temp;
                                        temp.reset();
                                        return true;
                                      }
                                    }
                                    theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                                    theGrid.at(i).at(j) = temp;
                                    temp.reset();
                                    
                                          
                                }
                            } 
                    }
    
            }
        }
    }
    return false;
}


// isstalemate
bool Grid::isstalemate(char colour){
    
    // check stalemate
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            
            // check nullptr
            if (theGrid.at(i).at(j) == nullptr) continue;
            
            if(theGrid.at(i).at(j)->get_colour() == colour){
               bool move = hasvalidmove(static_cast<X>(j), i, colour);
               if (move) {
                   return false;
               }
            }
            
        }
    }
    
    return  true;
    
}


// init
void Grid::init(std::vector<std::vector<std::shared_ptr<Chess>>> & newGrid){
    theGrid = newGrid;
    enpassant = false;
    ep_candidates.clear();
}


// setpiece
void Grid::setPiece(char type, X col, int row, char colour){
    if (type == 'R' || type == 'r'){
        
      theGrid.at(8-row).at(static_cast<int>(col)).reset();
	  theGrid.at(8-row).at(static_cast<int>(col)) = std::make_shared<Rook>(type, col, row, true, colour, true);
	  td->notify(row, col, type);
	  gd->notify(row, col, type);
	  
    } else if (type == 'N' || type == 'n'){
        
      theGrid.at(8-row).at(static_cast<int>(col)).reset();
	  theGrid.at(8-row).at(static_cast<int>(col)) = std::make_shared<Knight>(type, col, row, true, colour);
	  td->notify(row, col, type);
	  gd->notify(row, col, type);
	  
    } else if (type == 'B' || type == 'b'){
        
      theGrid.at(8-row).at(static_cast<int>(col)).reset();
	  theGrid.at(8-row).at(static_cast<int>(col)) = std::make_shared<Bishop>(type, col, row, true, colour);
	  td->notify(row, col, type);
	  gd->notify(row, col, type);
	  
    } else if (type == 'K' || type == 'k'){
        
      theGrid.at(8-row).at(static_cast<int>(col)).reset();
	  theGrid.at(8-row).at(static_cast<int>(col)) = std::make_shared<King>(type, col, row, true, colour, true);
	  td->notify(row, col, type);
	  gd->notify(row, col, type);
        
    } else if (type == 'Q' || type == 'q'){
        
      theGrid.at(8-row).at(static_cast<int>(col)).reset();
	  theGrid.at(8-row).at(static_cast<int>(col)) = std::make_shared<Queen>(type, col, row, true, colour);
	  td->notify(row, col, type);
	  gd->notify(row, col, type);
        
    } else if (type == 'P' || type == 'p') {
        
      theGrid.at(8-row).at(static_cast<int>(col)).reset();
	  theGrid.at(8-row).at(static_cast<int>(col)) = std::make_shared<Pawn>(type, col, row, true, colour, true);
	  td->notify(row, col, type);
	  gd->notify(row, col, type);
        
    }
}


// remove piece
void Grid::removePiece(X col, int row){
    if (theGrid.at(8-row).at(static_cast<int>(col)) == nullptr) {
        throw InvalidMove {};
    }
	if (((row % 2) == 0) && ((static_cast<int>(col) % 2) == 0)) {
		td->notify(row, col, ' ');
		gd->notify(row, col, ' ');
	} else if ((row % 2) == 0) {
		td->notify(row, col, '_');
		gd->notify(row, col, '_');
	} else if (static_cast<int>(col) % 2 == 0) {
		td->notify(row, col, '_');
		gd->notify(row, col, '_');
	} else {
		td->notify(row, col, ' ');
		gd->notify(row, col, ' ');
	}
	theGrid.at(8-row).at(static_cast<int>(col))->set_alive(false);
	theGrid.at(8-row).at(static_cast<int>(col)) = nullptr;
}	


// is occupy
bool Grid::isOccupy(X c, int r){
  if (theGrid.at(7-r+1).at(static_cast<int>(c))){
	  return true;
	} else {
      return false;
	}
}


//is_block
bool Grid::is_block(X old_x_cor, int old_y_cor, X x_cor, int y_cor, char colour) {
     if (theGrid.at(old_y_cor).at(static_cast<int>(old_x_cor)) == nullptr) return true;
     char c = theGrid.at(old_y_cor).at(static_cast<int>(old_x_cor))->get_colour();
     if(c != colour) return true;
     if (theGrid.at(y_cor).at(static_cast<int>(x_cor)) != nullptr){
       char c2 = theGrid.at(y_cor).at(static_cast<int>(x_cor))->get_colour();
       if (c2 == colour) return true;
       if (c == c2) return true;
     }
     
     int dist1 = abs(static_cast<int>(x_cor) - static_cast<int>(old_x_cor));
     int dist2 = abs(y_cor - old_y_cor);
     
     if(dist1 == 0 && dist2 == 0) return true;
     if(dist1 <= 1 && dist2 <= 1) return false;
     
     if (c != colour) {
         
         return true;//same colour as the destination, so it should be false
         
         
     } else if(old_y_cor == y_cor) {//horizontal

        int i = static_cast<int>(x_cor) - static_cast<int>(old_x_cor);
        if (i > 0) {//pos
          for (int k = i - 1; k > 0; k--) {
            if (theGrid.at(old_y_cor).at(static_cast<int>(old_x_cor) + k) != nullptr) return true;
          }
        } else {//neg
          for (int k = i + 1; k < 0; k++) {
            if (theGrid.at(old_y_cor).at(static_cast<int>(old_x_cor) + k) != nullptr) return true;
          }
        }
        
        return false;

    } else if( static_cast<int>(old_x_cor) ==  static_cast<int>(x_cor)) {//vertical

        int i = y_cor - old_y_cor;
        if (i > 0) {//pos
          for (int k = i - 1; k > 0; k--) {
            if (theGrid.at(old_y_cor + k).at(static_cast<int>(old_x_cor)) != nullptr) return true;
          }
        } else {//neg
          for (int k = i + 1; k < 0; k++) {
            if (theGrid.at(old_y_cor + k).at(static_cast<int>(old_x_cor)) != nullptr) return true;
          }
        }
        
        return false;

    } else if (dist1 == dist2){//slope
         int hor = static_cast<int>(x_cor) - static_cast<int>(old_x_cor);
         int ver = y_cor - old_y_cor;
         if (hor > 0 && ver > 0) {
             for (int i = hor - 1; i > 0; --i) {//NE
                  if (theGrid.at(old_y_cor + i).at(static_cast<int>(old_x_cor) + i) != nullptr) return true;
             }
         } else if (hor < 0 && ver < 0) {
            for (int i = hor + 1; i < 0; ++i) {//SW
                  if (theGrid.at(old_y_cor + i).at(static_cast<int>(old_x_cor) + i) != nullptr) return true;
             } 
         } else if (hor > 0 && ver < 0) {
            for (int i = hor - 1; i > 0; --i) {//SE
                  if (theGrid.at(old_y_cor - i).at(static_cast<int>(old_x_cor) + i) != nullptr) return true;
             } 
         } else {
            for (int i = ver - 1; i > 0; --i) {//NW
                  if (theGrid.at(old_y_cor + i).at(static_cast<int>(old_x_cor) - i) != nullptr) return true;
             }
         }
         
         return false;
         
    } else {//knight move
        return false;
    }
    
}


// computer1_move

//void Grid::computer1_move(char colour){}
void Grid::computer1_move(std::shared_ptr <Chess> sour, std::vector<int> dest) {
    int r1 = 8 - sour->get_y();
    X c1 = sour->get_x();
    int r2 = dest.at(0);
    X c2 = static_cast<X>(dest.at(1));
    
    std::shared_ptr<Chess> temp = theGrid.at(r2).at(static_cast<int>(c2));
    
    
    if (theGrid.at(r2).at(static_cast<int>(c2)) != nullptr){
        // set alive
        theGrid.at(r2).at(static_cast<int>(c2))->set_alive(false);
    }
    
    
    theGrid.at(r1).at(static_cast<int>(c1)).swap(theGrid.at(r2).at(static_cast<int>(c2)));
    theGrid.at(r1).at(static_cast<int>(c1)).reset();
    theGrid.at(r1).at(static_cast<int>(c1)) = nullptr;
    
     // set new pos
    theGrid.at(r2).at(static_cast<int>(c2))->new_pos(c2, 8 - r2);
    
        
    // notify td and gd
    char type = theGrid.at(r2).at(static_cast<int>(c2))->get_name();
        
        
    // bool upper = isupper(type);
    if ((r1 % 2 == 0 && static_cast<int>(c1) % 2 == 0) || (r1 % 2 != 0 && static_cast<int>(c1) % 2 != 0)){
        td->notify(8 - r1, c1, ' ');
        gd->notify(8 - r1, c1, ' ');
    } else {
       td->notify(8 - r1, c1, '_');
       gd->notify(8 - r1, c1, '_');
    }
    
    td->notify(8 - r2, c2, type);
    gd->notify(8 - r2, c2, type);
    
    // add move to undo list
    std::vector<int> tmp;
    tmp.emplace_back(static_cast<int>(c1));
    tmp.emplace_back(r1);
    tmp.emplace_back(static_cast<int>(c2));
    tmp.emplace_back(r2);
    
    
    
    if (temp != nullptr){
        if (temp->get_name() == 'Q') {
                tmp.emplace_back(1);
                tmp.emplace_back(0);
        } else if (temp->get_name() == 'q') {
          	    tmp.emplace_back(1);
          	    tmp.emplace_back(1);
        } else if (temp->get_name() == 'R'){
          	    tmp.emplace_back(2);
          	    tmp.emplace_back(0);
        } else if (temp->get_name() == 'r'){
          	    tmp.emplace_back(2);
          	    tmp.emplace_back(1);
        } else if (temp->get_name() == 'B') {
          	    tmp.emplace_back(3);
          	    tmp.emplace_back(0);
        } else if (temp->get_name() == 'b'){
          	    tmp.emplace_back(3);
          	    tmp.emplace_back(1);
        } else if (temp->get_name() == 'N') {
          	    tmp.emplace_back(4);
          	    tmp.emplace_back(0);
        } else if (temp->get_name() == 'n') {
          	    tmp.emplace_back(4);
          	    tmp.emplace_back(1);
        } else if (temp->get_name() == 'P') {
          	    tmp.emplace_back(5);
          	    tmp.emplace_back(0);
        } else {
          	    tmp.emplace_back(5);
          	    tmp.emplace_back(1);
        }
    } 
    
    
    undo_list.emplace_back(tmp);
    
    temp.reset();
    
}


// computer2_move
void Grid::computer2_move(std::shared_ptr <Chess> sour, std::vector<int> dest){
    
    int r1 = 8 - sour->get_y();
    X c1 = sour->get_x();
    int r2 = dest.at(0);
    X c2 = static_cast<X>(dest.at(1));
    char colour = sour->get_colour();
    
    std::shared_ptr<Chess> temp = theGrid.at(r2).at(static_cast<int>(c2));
    
    
    this->move(c1, r1, c2, r2, colour);
    
    std::vector<int> tmp;
    tmp.emplace_back(static_cast<int>(c1));
    tmp.emplace_back(r1);
    tmp.emplace_back(static_cast<int>(c2));
    tmp.emplace_back(r2);
    
    
    
    if (temp != nullptr){
        if (temp->get_name() == 'Q') {
                tmp.emplace_back(1);
                tmp.emplace_back(0);
        } else if (temp->get_name() == 'q') {
          	    tmp.emplace_back(1);
          	    tmp.emplace_back(1);
        } else if (temp->get_name() == 'R'){
          	    tmp.emplace_back(2);
          	    tmp.emplace_back(0);
        } else if (temp->get_name() == 'r'){
          	    tmp.emplace_back(2);
          	    tmp.emplace_back(1);
        } else if (temp->get_name() == 'B') {
          	    tmp.emplace_back(3);
          	    tmp.emplace_back(0);
        } else if (temp->get_name() == 'b'){
          	    tmp.emplace_back(3);
          	    tmp.emplace_back(1);
        } else if (temp->get_name() == 'N') {
          	    tmp.emplace_back(4);
          	    tmp.emplace_back(0);
        } else if (temp->get_name() == 'n') {
          	    tmp.emplace_back(4);
          	    tmp.emplace_back(1);
        } else if (temp->get_name() == 'P') {
          	    tmp.emplace_back(5);
          	    tmp.emplace_back(0);
        } else {
          	    tmp.emplace_back(5);
          	    tmp.emplace_back(1);
        }
    } 
    
    
    undo_list.emplace_back(tmp);
    
    temp.reset();
    
    
}


// computer3_move
void Grid::computer3_move(char colour){}


// computer4_move
void Grid::computer4_move(char colour){}


void Grid::isenpassant(X old_c, int old_r, X new_c, int new_r){
    
     // check pawn
     if (theGrid.at(old_r).at(static_cast<int>(old_c))->get_name() == 'P' || 
         theGrid.at(old_r).at(static_cast<int>(old_c))->get_name() == 'p'){
           //std::shared_ptr<Pawn> p = std::static_pointer_cast<Pawn>(theGrid.at(old_r).at(static_cast<int>(old_c)));
           
           // check 2 steps move
           if (abs(new_r - old_r) == 2){
               
               bool upper = isupper(theGrid.at(old_r).at(static_cast<int>(old_c))->get_name());
               
               // check captured by other pawn
               if (upper){
                   ep_r = old_r - 1;
                   ep_c = old_c;
                   
                   ep_eat_r = new_r;
                   ep_eat_c = new_c;
                   
                   // check boundaries??
                   if (( 0 <= ep_r - 1 && ep_r - 1 < 8) && (0 <= static_cast<int>(ep_c) + 1 && static_cast<int>(ep_c) + 1 < 8)) {
                     if (theGrid.at(ep_r - 1).at(static_cast<int>(ep_c) + 1) != nullptr){
                        if (theGrid.at(ep_r - 1).at(static_cast<int>(ep_c) + 1)->get_name() == 'p'){
                            ep_candidates.emplace_back(theGrid.at(ep_r - 1).at(static_cast<int>(ep_c) + 1)); // add candidates
                            enpassant  =true;  // enpassant!!!
                        }
                     }
                   }
                   
                   if (( 0 <= ep_r - 1 && ep_r - 1 < 8) && (0 <= static_cast<int>(ep_c) - 1 && static_cast<int>(ep_c) - 1 < 8)){
                     if (theGrid.at(ep_r - 1).at(static_cast<int>(ep_c) - 1) != nullptr) {
                         if (theGrid.at(ep_r - 1).at(static_cast<int>(ep_c) - 1)->get_name() == 'p'){
                            ep_candidates.emplace_back(theGrid.at(ep_r - 1).at(static_cast<int>(ep_c) - 1)); // add candidates
                            enpassant  =true;  // enpassant!!!
                        }
                     }
                   }
                   
               } else {
                   ep_r = old_r + 1;
                   ep_c = old_c;
                   
                   ep_eat_r = new_r;
                   ep_eat_c = new_c;
                   
                   if (( 0 <= ep_r + 1 && ep_r + 1 < 8) && (0 <= static_cast<int>(ep_c) + 1 && static_cast<int>(ep_c) + 1 < 8)){
                     if (theGrid.at(ep_r + 1).at(static_cast<int>(ep_c) + 1) != nullptr){
                        if (theGrid.at(ep_r + 1).at(static_cast<int>(ep_c) + 1)->get_name() == 'P'){
                            ep_candidates.emplace_back(theGrid.at(ep_r + 1).at(static_cast<int>(ep_c) + 1)); // add candidates
                           enpassant  =true;  // enpassant!!!
                        }
                     }
                   }
                   
                   if (( 0 <= ep_r + 1 && ep_r + 1 < 8) && (0 <= static_cast<int>(ep_c) - 1 && static_cast<int>(ep_c) - 1 < 8)){
                     if (theGrid.at(ep_r + 1).at(static_cast<int>(ep_c) - 1) != nullptr) {
                         if (theGrid.at(ep_r + 1).at(static_cast<int>(ep_c) - 1)->get_name() == 'P'){
                            ep_candidates.emplace_back(theGrid.at(ep_r + 1).at(static_cast<int>(ep_c) - 1)); // add candidates
                            enpassant  =true;  // enpassant!!!
                        }
                     }
                   }
                   
               }
               
               
               
           }
     } 
     
}


bool Grid::enpassant_move(X old_c, int old_r, X new_c, int new_r){
    if (new_c == ep_c && new_r == ep_r){
        for(size_t i = 0; i < ep_candidates.size(); ++i){
            if (theGrid.at(old_r).at(static_cast<int>(old_c)) == ep_candidates.at(i)){
                
                // enpassant move
                theGrid.at(ep_eat_r).at(static_cast<int>(ep_eat_c)).reset();
                theGrid.at(ep_eat_r).at(static_cast<int>(ep_eat_c)) = nullptr;
                
                theGrid.at(old_r).at(static_cast<int>(old_c)).swap(theGrid.at(new_r).at(static_cast<int>(new_c)));
                theGrid.at(old_r).at(static_cast<int>(old_c)).reset();
			    theGrid.at(old_r).at(static_cast<int>(old_c)) = nullptr;
                
                char type = theGrid.at(new_r).at(static_cast<int>(new_c))->get_name();
                
                if ((ep_eat_r % 2 == 0 && static_cast<int>(ep_eat_c) % 2 == 0) || (ep_eat_r % 2 != 0 && static_cast<int>(ep_eat_c) % 2 != 0)){
                    td->notify(8 - ep_eat_r, ep_eat_c, ' ');
                    gd->notify(8 - ep_eat_r, ep_eat_c, ' ');
                } else {
                    td->notify(8 - ep_eat_r, ep_eat_c, '_');
                    gd->notify(8 - ep_eat_r, ep_eat_c, '_');
                }
                
                if ((old_r % 2 == 0 && static_cast<int>(old_c) % 2 == 0) || (old_r % 2 != 0 && static_cast<int>(old_c) % 2 != 0)){
                    td->notify(8 - old_r, old_c, ' ');
                    gd->notify(8 - old_r, old_c, ' ');
                } else {
                    td->notify(8 - old_r, old_c, '_');
                    gd->notify(8 - old_r, old_c, '_');
                }
                
                td->notify(8 - new_r, new_c, type);
                gd->notify(8 - new_r, new_c, type);
                
                
                enpassant = false;
                return true;
            }
        }
    } 
    
      enpassant = false;   
      return false;
}





// add td
void Grid::addtd(std::shared_ptr<TextDisplay> newtd){
    this->td = newtd;
}


// add gd
void Grid::addgd(std::shared_ptr<GraphicsDisplay> newgd){
   this->gd = newgd;
}

// checkdone
bool Grid::checkdone(){
	//checks if there are pawns on the last row and first row. 
	for (int i = 0; i < 8; i++) {
		if (theGrid.at(0).at(i) != nullptr) {
			if ((theGrid.at(0).at(i)->get_name() == 'P') || (theGrid.at(0).at(i)->get_name() == 'p')) return false;
		}
		if (theGrid.at(7).at(i) != nullptr) {
			if ((theGrid.at(7).at(i)->get_name() == 'P') || (theGrid.at(7).at(i)->get_name() == 'p')) return false;
		}
	}
	
	// checks if there is exactly one King. 
	int black_king = 0;
	int white_king = 0;
	
	for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (theGrid.at(i).at(j) == nullptr) continue;
            if (theGrid.at(i).at(j)->get_name() == 'K') {
                ++white_king;
            }
            if (theGrid.at(i).at(j)->get_name() == 'k') {
                ++black_king;
            }
        }
	}
	
	if ((black_king != 1) || (white_king != 1)) return false;
	
	// checks if it leaves the king in check. 
	if (ischeck('B') || ischeck('W')) return false;
	
	// otherwise: 
	return true;
}
  
// clear
void Grid::clear() {
   theGrid.clear();
}


void Grid::findvalidmove(std::shared_ptr<Chess> c, std::vector<std::vector<int>> & candidates){
     int row = 8 - c->get_y();
     X col = c->get_x();
     char colour = c->get_colour();
     for (int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            // check nullptr
            if (theGrid.at(i).at(j) != nullptr){
                
                // check colour
                if (theGrid.at(i).at(j)->get_colour() != colour){
                    
                    // check pawn attack
                    char type = theGrid.at(row).at(static_cast<int>(col))->get_name();
                    if (colour == 'W' && type == 'P' && (row == i + 1) && (static_cast<int>(col) == j - 1 ||
                        static_cast<int>(col) == j + 1)){ // black attack white
                        
                        // check is check
                        theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                   
                        std::shared_ptr<Chess> temp = theGrid.at(row).at(static_cast<int>(col));
                        theGrid.at(row).at(static_cast<int>(col)).reset();
                        theGrid.at(row).at(static_cast<int>(col)) = nullptr;            
                            
                            
                        bool check1 = ischeck('W');  
                        if (!check1){
                            
                            // add candidates
                            std::vector<int> v;
                            v.emplace_back(i);
                            v.emplace_back(j);
                            candidates.emplace_back(v);
                        }
                        
                        theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                        theGrid.at(i).at(j) = temp;
                        temp.reset();
                        
                        
                    } else if (colour == 'B' && type == 'p' && (row == i - 1) && (static_cast<int>(col) == j - 1 ||
                      static_cast<int>(col) == j + 1)) { // white attack black
                          
                        // check is check
                        theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                   
                        std::shared_ptr<Chess> temp = theGrid.at(row).at(static_cast<int>(col));
                        theGrid.at(row).at(static_cast<int>(col)).reset();
                        theGrid.at(row).at(static_cast<int>(col)) = nullptr;            
                            
                            
                        bool check2 = ischeck('B');  
                        if (!check2){
                            
                            // add candidates
                            std::vector<int> v;
                            v.emplace_back(i);
                            v.emplace_back(j);
                            candidates.emplace_back(v);
                            
                        }
                        theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                        theGrid.at(i).at(j) = temp;
                        temp.reset();
                        
                    } else if (colour == 'W' && type == 'P' ){
                        continue;
                    } else if (colour == 'B' && type == 'p') {
                        continue;
                    } 
                        
                    
                    
                    // check valid move
                    bool valid1 = theGrid.at(row).at(static_cast<int>(col))->valid(static_cast<X>(j), 8 - i);
                    
                    if (valid1){
                        bool block1 = is_block(col, row, static_cast<X>(j), i,  colour);
                        if (!block1){
                            
                            // check is check
                            theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                   
                            std::shared_ptr<Chess> temp = theGrid.at(row).at(static_cast<int>(col));
                            theGrid.at(row).at(static_cast<int>(col)).reset();
                            theGrid.at(row).at(static_cast<int>(col)) = nullptr;            
                            
                            if (colour == 'W'){
                              bool check3 = ischeck('W');
                              if (!check3){
                                 
                                // add candidates
                                std::vector<int> v;
                                v.emplace_back(i);
                                v.emplace_back(j);
                                candidates.emplace_back(v);
                                
                              }
                              
                            } else {
                              bool check4 = ischeck('B');  
                              if (!check4){
                                  
                                    // add candidates
                                    std::vector<int> v;
                                    v.emplace_back(i);
                                    v.emplace_back(j);
                                    candidates.emplace_back(v);
                              }
                            }
                            theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                            theGrid.at(i).at(j) = temp;
                            temp.reset();
                                  
                        }
                    }
                    
                    
                    
                    
                } else {
                   continue;    
                }
            } else { // nullptr
            
                // check enpassant
                if (enpassant == true){
                   if (ep_c == static_cast<X>(j) && ep_r == i){
                        for(size_t i = 0; i < ep_candidates.size(); ++i){
                             if (theGrid.at(row).at(static_cast<int>(col)) == ep_candidates.at(i)){
                                 
                                // check
                                std::shared_ptr<Chess> temp1 = theGrid.at(ep_eat_r).at(static_cast<int>(ep_eat_c));
                                theGrid.at(ep_eat_r).at(static_cast<int>(ep_eat_c)).reset();
                                theGrid.at(ep_eat_r).at(static_cast<int>(ep_eat_c)) = nullptr;
                                
                                // swap
                                theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                                
                                std::shared_ptr<Chess> temp2 = theGrid.at(row).at(static_cast<int>(col));
                                theGrid.at(row).at(static_cast<int>(col)).reset();
                			    theGrid.at(row).at(static_cast<int>(col)) = nullptr;
                                
                                bool check5 = ischeck(colour);
                                if (!check5){
                                    
                                    // add candidates
                                    std::vector<int> v;
                                    v.emplace_back(i);
                                    v.emplace_back(j);
                                    candidates.emplace_back(v);
                                    
                                }
                                theGrid.at(ep_eat_r).at(static_cast<int>(ep_eat_c)) = temp1;
                                    
                                theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                                theGrid.at(i).at(j) = temp2;
                                temp1.reset();
                                temp2.reset();
                             }
                        }
                   }
                }
                
                
                // check castling
                bool castle = castling(col, row, static_cast<X>(j), i, colour);
                if (castle){
                    castle_move(colour, static_cast<X>(j));
                    if (colour == 'W'){
                        bool check6 = ischeck('W');
                        
                        if (check6 == false) {
                            
                             // add candidates
                            std::vector<int> v;
                            v.emplace_back(i);
                            v.emplace_back(j);
                            candidates.emplace_back(v);
                            
                        }
                        
                        if (static_cast<X>(j) == X::g || static_cast<X>(j) == X::f) { //bot right
                            theGrid.at(7).at(static_cast<int>(4)).swap(theGrid.at(7).at(static_cast<int>(6)));
                            theGrid.at(7).at(static_cast<int>(4))->new_pos(X::e, 1);
                            theGrid.at(7).at(static_cast<int>(5)).swap(theGrid.at(7).at(static_cast<int>(7)));
                            theGrid.at(7).at(static_cast<int>(7))->new_pos(X::h, 1);
                        } else {//left bot
                            theGrid.at(7).at(0).swap(theGrid.at(7).at(3));
                            theGrid.at(7).at(0)->new_pos(X::a, 1);
                            theGrid.at(7).at(2).swap(theGrid.at(7).at(4));
                            theGrid.at(7).at(4)->new_pos(X::e, 1);
                        }
                        
                        
                    } else {
                        bool check7 = ischeck('B');
                                 
                        if (check7 == false) {
                            
                            // add candidates
                            std::vector<int> v;
                            v.emplace_back(i);
                            v.emplace_back(j);
                            candidates.emplace_back(v);
                            
                        }
                        
                        if (static_cast<X>(j) == X::g || static_cast<X>(j) == X::f) { //top right
                            theGrid.at(0).at(static_cast<int>(4)).swap(theGrid.at(0).at(static_cast<int>(6)));
                            theGrid.at(0).at(static_cast<int>(4))->new_pos(X::e, 8);
                            theGrid.at(0).at(static_cast<int>(5)).swap(theGrid.at(0).at(static_cast<int>(7)));
                            theGrid.at(0).at(static_cast<int>(7))->new_pos(X::h, 8);
                        } else {
                            theGrid.at(0).at(0).swap(theGrid.at(0).at(3));
                            theGrid.at(0).at(0)->new_pos(X::a, 8);
                            theGrid.at(0).at(2).swap(theGrid.at(0).at(4));
                            theGrid.at(0).at(4)->new_pos(X::e, 8);
                        }
                        
                    }
                    
                } else {
                
                
                
                
                
                // check valid move
                bool valid2 = theGrid.at(row).at(static_cast<int>(col))->valid(static_cast<X>(j), 8 - i);
                    
                    if (valid2){
                        bool block2 = is_block(col, row, static_cast<X>(j), i, colour);
                        if (!block2){
                            
                            // check enpassant
                            isenpassant(col, row, static_cast<X>(j), i);
                            
                            if (enpassant){
                                enpassant = false;
                                continue;
                            }
                            
                            
                            // check pawn move
                            if(theGrid.at(row).at(static_cast<int>(col))->get_name() == 'P' || theGrid.at(row).at(static_cast<int>(col))->get_name() == 'p'){
                                if (std::static_pointer_cast<Pawn>(theGrid.at(row).at(static_cast<int>(col)))->get_first() == false && abs(row -i) == 2){
                                    continue;
                                }
                                
                            }
                            
                            // check is check
                            theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                   
                            std::shared_ptr<Chess> temp = theGrid.at(row).at(static_cast<int>(col));
                            theGrid.at(row).at(static_cast<int>(col)).reset();
                            theGrid.at(row).at(static_cast<int>(col)) = nullptr;            
                            
                            if (colour == 'W'){
                              bool check3 = ischeck('W');
                              if (!check3){
                                  
                                // add candidates
                                std::vector<int> v;
                                v.emplace_back(i);
                                v.emplace_back(j);
                                candidates.emplace_back(v);
                              } 
                              
                            } else {
                              bool check4 = ischeck('B');  
                              if (!check4){
                                // add candidates
                                std::vector<int> v;
                                v.emplace_back(i);
                                v.emplace_back(j);
                                candidates.emplace_back(v);
                                
                              }
                            }
                            theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                            theGrid.at(i).at(j) = temp;
                            temp.reset();
                            
                                  
                        }
                    } 
                }
            }
        }
    }
}

// search_best_move
void Grid::search_best_move(std::shared_ptr<Chess> c, std::vector<std::vector<int>> & candidates, 
                            std::vector<Attack> & best_attacks, int & move_level){
    
    //int best_col = candidates.at(0).at(1);
    //int best_row = candidates.at(0).at(0);
    
    for(size_t i = 0; i < candidates.size(); ++i){
        int row = candidates.at(i).at(0);
        int col = candidates.at(i).at(1);
        
        if (theGrid.at(row).at(col) != nullptr){
            
            if (move_level == 0){
                
                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                
                bool check;
                if (c->get_colour() == 'W'){
                    check = ischeck('B');
                } else {
                    check = ischeck('W');
                }
                
                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                theGrid.at(row).at(col) = temp;
                temp.reset();
                
                
                if (check){
                    best_attacks.clear();
                    move_level = 2;
                    best_attacks.emplace_back(Attack{c, row, col});
                } else {
                    best_attacks.clear();
                    move_level = 1;
                    best_attacks.emplace_back(Attack{c, row, col});
                }
                
            } else if (move_level == 1){
                
                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                
                bool check;
                if (c->get_colour() == 'W'){
                    check = ischeck('B');
                } else {
                    check = ischeck('W');
                }
                
                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                theGrid.at(row).at(col) = temp;
                temp.reset();
                
                
                if (check){
                    best_attacks.clear();
                    move_level = 2;
                    best_attacks.emplace_back(Attack{c, row, col});
                } else {
                    best_attacks.emplace_back(Attack{c, row, col});
                }
                
            } else if (move_level == 2) {
                
                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                
                bool check;
                if (c->get_colour() == 'W'){
                    check = ischeck('B');
                } else {
                    check = ischeck('W');
                }
                
                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                theGrid.at(row).at(col) = temp;
                temp.reset();
                
                if (check){
                    best_attacks.emplace_back(Attack{c, row, col});
                }
                
            }
            
        } else {
            if (move_level == 0){
                best_attacks.emplace_back(Attack{c, row, col});
            }
        }
        
    }
    
    
    
}

// search_best_move3
// first considering current location captured by other chess, then considering move location captured, last check or capture opponent 
void Grid::search_best_move3(std::shared_ptr<Chess> c, std::vector<std::vector<int>> & candidates, 
                            std::vector<Attack> & best_attacks, int & move_level, int & captured_level, int & is_captured_level){
                                
    // check current location is captured
    
    bool current_captured = check_captured(c->get_x(), 8 - c->get_y(), c->get_colour());
    if (current_captured){
        if (is_captured_level == 0){
            // current_captured & is_captured_level == 0
            
            
            // captured, emergency!!!
            is_captured_level = 1;
            
            // reset everything
            best_attacks.clear();
            move_level = 0;
            captured_level = 0;
            
             for(size_t i = 0; i < candidates.size(); ++i){
                int row = candidates.at(i).at(0);
                int col = candidates.at(i).at(1);
                char colour = c->get_colour();
                
                // check captured
                bool captured = check_captured(static_cast<X>(col), row, colour);
                    
                    
                if (captured_level == 0){
                    if (captured){
                        
                        // check move_level
                        if (theGrid.at(row).at(col) != nullptr){
                    
                            if (move_level == 0){
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    
                                    // check captured
                                    
                                    best_attacks.clear();
                                    move_level = 2;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                } else {
                                    
                                    
                                    best_attacks.clear();
                                    move_level = 1;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            } else if (move_level == 1){
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    best_attacks.clear();
                                    move_level = 2;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                } else {
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            } else if (move_level == 2) {
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            }
                        
                        } else {
                            if (move_level == 0){
                                best_attacks.emplace_back(Attack{c, row, col});
                            }
                        }
                    } else {
                        
                        // clear best_attacks
                        best_attacks.clear();
                        
                        // reset move level
                        move_level = 0;
                        
                        // change captured_level
                        captured_level = 1;
                        
                        // check move_level
                        if (theGrid.at(row).at(col) != nullptr){
                            
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                
                                if (check){
                                    
                                    // check checkmate
                                    
                                    best_attacks.clear();
                                    move_level = 2;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                } else {
                                    
                                    // check captured
                                    
                                    best_attacks.clear();
                                    move_level = 1;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                        } else {
        
                                best_attacks.emplace_back(Attack{c, row, col});
                                
                        }
                    }
                    
                } else {
                    if (captured){
                        continue;
                    } else {
                        
                        // check move_level
                        if (theGrid.at(row).at(col) != nullptr){
                    
                            if (move_level == 0){
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    
                                    // check captured
                                    
                                    best_attacks.clear();
                                    move_level = 2;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                } else {
                                    
                                    
                                    best_attacks.clear();
                                    move_level = 1;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            } else if (move_level == 1){
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    best_attacks.clear();
                                    move_level = 2;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                } else {
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            } else if (move_level == 2) {
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            }
                        
                        } else {
                            if (move_level == 0){
                                best_attacks.emplace_back(Attack{c, row, col});
                            }
                        }
                        
                        
                    }
                    
                }
                
                
                
            }
            
            
            
        } else {
            // current_captured & is_captured_level == 1
            
            for(size_t i = 0; i < candidates.size(); ++i){
                int row = candidates.at(i).at(0);
                int col = candidates.at(i).at(1);
                char colour = c->get_colour();
                
                // check captured
                bool captured = check_captured(static_cast<X>(col), row, colour);
                    
                    
                if (captured_level == 0){
                    if (captured){
                        
                        // check move_level
                        if (theGrid.at(row).at(col) != nullptr){
                    
                            if (move_level == 0){
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    
                                    // check captured
                                    
                                    best_attacks.clear();
                                    move_level = 2;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                } else {
                                    
                                    
                                    best_attacks.clear();
                                    move_level = 1;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            } else if (move_level == 1){
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    best_attacks.clear();
                                    move_level = 2;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                } else {
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            } else if (move_level == 2) {
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            }
                        
                        } else {
                            if (move_level == 0){
                                best_attacks.emplace_back(Attack{c, row, col});
                            }
                        }
                    } else {
                        
                        // clear best_attacks
                        best_attacks.clear();
                        
                        // reset move level
                        move_level = 0;
                        
                        // change captured_level
                        captured_level = 1;
                        
                        // check move_level
                        if (theGrid.at(row).at(col) != nullptr){
                            
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                
                                if (check){
                                    
                                    // check checkmate
                                    
                                    best_attacks.clear();
                                    move_level = 2;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                } else {
                                    
                                    // check captured
                                    
                                    best_attacks.clear();
                                    move_level = 1;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                        } else {
        
                                best_attacks.emplace_back(Attack{c, row, col});
                                
                        }
                    }
                    
                } else {
                    if (captured){
                        continue;
                    } else {
                        
                        // check move_level
                        if (theGrid.at(row).at(col) != nullptr){
                    
                            if (move_level == 0){
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    
                                    // check captured
                                    
                                    best_attacks.clear();
                                    move_level = 2;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                } else {
                                    
                                    
                                    best_attacks.clear();
                                    move_level = 1;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            } else if (move_level == 1){
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    best_attacks.clear();
                                    move_level = 2;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                } else {
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            } else if (move_level == 2) {
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            }
                        
                        } else {
                            if (move_level == 0){
                                best_attacks.emplace_back(Attack{c, row, col});
                            }
                        }
                        
                        
                    }
                    
                }
                
                
                
            }
            
            
        }
    } else {
        // not current_capture
        if (is_captured_level == 0){
            // not current_capture & is_captured_levle == 0 (add)
            for(size_t i = 0; i < candidates.size(); ++i){
                int row = candidates.at(i).at(0);
                int col = candidates.at(i).at(1);
                char colour = c->get_colour();
                
                // check captured
                bool captured = check_captured(static_cast<X>(col), row, colour);
                    
                    
                if (captured_level == 0){
                    if (captured){
                        
                        // check move_level
                        if (theGrid.at(row).at(col) != nullptr){
                    
                            if (move_level == 0){
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    
                                    // check captured
                                    
                                    best_attacks.clear();
                                    move_level = 2;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                } else {
                                    
                                    
                                    best_attacks.clear();
                                    move_level = 1;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            } else if (move_level == 1){
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    best_attacks.clear();
                                    move_level = 2;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                } else {
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            } else if (move_level == 2) {
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            }
                        
                        } else {
                            if (move_level == 0){
                                best_attacks.emplace_back(Attack{c, row, col});
                            }
                        }
                    } else {
                        
                        // clear best_attacks
                        best_attacks.clear();
                        
                        // reset move level
                        move_level = 0;
                        
                        // change captured_level
                        captured_level = 1;
                        
                        // check move_level
                        if (theGrid.at(row).at(col) != nullptr){
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    
                                    // check checkmate
                                    
                                    best_attacks.clear();
                                    move_level = 2;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                } else {
                                    
                                    // check captured
                                    
                                    best_attacks.clear();
                                    move_level = 1;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                        } else {
        
                                best_attacks.emplace_back(Attack{c, row, col});
                                
                        }
                    }
                    
                } else {
                    if (captured){
                        continue;
                    } else {
                        
                        // check move_level
                        if (theGrid.at(row).at(col) != nullptr){
                    
                            if (move_level == 0){
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    
                                    
                                    
                                    // check captured
                                    
                                    best_attacks.clear();
                                    move_level = 2;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                } else {
                                    
                                    
                                    best_attacks.clear();
                                    move_level = 1;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            } else if (move_level == 1){
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    best_attacks.clear();
                                    move_level = 2;
                                    best_attacks.emplace_back(Attack{c, row, col});
                                } else {
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            } else if (move_level == 2) {
                                
                                std::shared_ptr<Chess> temp = theGrid.at(row).at(col);
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).reset();
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())) = nullptr;
                                
                                bool check;
                                if (c->get_colour() == 'W'){
                                    check = ischeck('B');
                                } else {
                                    check = ischeck('W');
                                }
                                
                                theGrid.at(8 - c->get_y()).at(static_cast<int>(c->get_x())).swap(theGrid.at(row).at(col));
                                theGrid.at(row).at(col) = temp;
                                temp.reset();
                                
                                if (check){
                                    best_attacks.emplace_back(Attack{c, row, col});
                                }
                                
                            }
                        
                        } else {
                            if (move_level == 0){
                                best_attacks.emplace_back(Attack{c, row, col});
                            }
                        }
                        
                        
                    }
                    
                }
                
                
                
            }
            
        } else {
            // not current_capture & is_captured_levle == 1
            
            // just continue, other current_captured chess have priority
            
        }
        
        
    }
    
    
}

// check_captured
bool Grid::check_captured(X col, int row, char colour){
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            
            // check null
            if (theGrid.at(i).at(j) == nullptr) continue;
            
            char attacker_colour = theGrid.at(i).at(j)->get_colour();
            
            // check colour
            if (attacker_colour != colour){
                
                char attacker_type = theGrid.at(i).at(j)->get_name();
                 
                 
                 // check enpassant
                 isenpassant(static_cast<X>(j), i, col, row);
                 if (enpassant){
                     enpassant = false;
                     return true;
                 }
                 
                 
                 // check pawn attack
                 if (attacker_colour == 'W' && attacker_type == 'P' && (row == i - 1) && (static_cast<int>(col) == j - 1 ||
                        static_cast<int>(col) == j + 1)){
                    return true;
                } else if (attacker_colour == 'B' && attacker_type == 'p' && (row == i + 1) && (static_cast<int>(col) == j - 1 ||
                        static_cast<int>(col) == j + 1)) {
                            
                    return true;      
                    
                } else if (attacker_colour == 'W' && attacker_type == 'P' ){
                    
                    continue;
                    
                } else if (attacker_colour == 'B' && attacker_type == 'p') {
                    
                    continue;
                    
                } else {
                    
                     bool valid = theGrid.at(i).at(j)->valid(col, 8 - row);
                     if (valid){
                          bool block = is_block(static_cast<X>(j), i, col, row, attacker_colour);
                          if (!block){
                              return true;
                          }
                     }
                    
                    
                }
                
            }
            
            
        }
    }
    return false;
}


// output operator
std::ostream & operator<<(std::ostream &out, const Grid & g) {
   return out;
}
