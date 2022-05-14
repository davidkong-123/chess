#include "grid.h"

// human move
void Grid::move(X old_c, int old_r, X new_c, int new_r, char colour){
    
    // check null
    if (theGrid.at(old_r).at(static_cast<int>(old_c)) == nullptr) {
        throw InvalidMove{};
    }
    
    
    // check boundaries
    if (static_cast<int>(old_c) > 7 || static_cast<int>(old_c) < 0 || old_r > 7 || old_r < 0 ||
        static_cast<int>(new_c) > 7 || static_cast<int>(new_c) < 0 || new_r > 7 || new_r < 0 ){
        throw InvalidMove{};
    }
    
    
    bool success = false;
    
    // check enpassant
    if (enpassant == true){
        success = enpassant_move(old_c, old_r,new_c,new_r);
    } 
        
    if (success) {
        return;
    }
    
    // check castling
    bool castle = castling(old_c, old_r, new_c, new_r, colour);
    if (castle){
        castle_move(colour, new_c);
        
        
        if (colour == 'W'){
            bool check1 = ischeck('W');
            
            if (check1 == true) {
                
                theGrid.at(7).at(static_cast<int>(4)).swap(theGrid.at(7).at(static_cast<int>(6)));
                theGrid.at(7).at(static_cast<int>(4))->new_pos(X::e, 1);
                theGrid.at(7).at(static_cast<int>(5)).swap(theGrid.at(7).at(static_cast<int>(7)));
                theGrid.at(7).at(static_cast<int>(7))->new_pos(X::h, 1);
                std::cout << "You cannot do that, the king wiil be checked" << std::endl;
                throw InvalidMove{};
            }
            
            if (ischeck('B')) std::cout << "Black is in check." << std::endl;
        } else {
            bool check1 = ischeck('B');
                     
            if (check1 == true) {
                theGrid.at(0).at(static_cast<int>(4)).swap(theGrid.at(0).at(static_cast<int>(6)));
                theGrid.at(0).at(static_cast<int>(4))->new_pos(X::e, 8);
                theGrid.at(0).at(static_cast<int>(5)).swap(theGrid.at(0).at(static_cast<int>(7)));
                theGrid.at(0).at(static_cast<int>(7))->new_pos(X::h, 8);
                std::cout << "You cannot do that, the king wiil be checked" << std::endl;
                throw InvalidMove{};
            }
            
            if (ischeck('W')) std::cout << "White is in check." << std::endl;
        }
    
      return;   
    }  else {
    
    
    
        // check pawn attack
        char ispawn = theGrid.at(old_r).at(static_cast<int>(old_c))->get_name();
        
        if (ispawn == 'P' && (old_r == new_r + 1) && (static_cast<int>(old_c) == static_cast<int>(new_c) - 1 || static_cast<int>(old_c) == static_cast<int>(new_c) + 1)){
            if (colour == 'B'){
            
                // check my colour
                throw InvalidMove{};
            } else {
                
                
                char new_colour = theGrid.at(new_r).at(static_cast<int>(new_c))->get_colour();
            
                if (new_colour == 'W'){
                
                    // check new colour
                    throw InvalidMove{};
                } else if (theGrid.at(new_r).at(static_cast<int>(new_c)) == nullptr) {
                
                    // check new piece
                    throw InvalidMove{};
                } else {
                
                    // move and set alive
                    theGrid.at(new_r).at(static_cast<int>(new_c))->set_alive(false);
                    theGrid.at(old_r).at(static_cast<int>(old_c)).swap(theGrid.at(new_r).at(static_cast<int>(new_c)));
                    theGrid.at(old_r).at(static_cast<int>(old_c)).reset();
    			    theGrid.at(old_r).at(static_cast<int>(old_c)) = nullptr;
                }
            }
        
        } else if (ispawn == 'p' && (old_r == new_r - 1) && (static_cast<int>(old_c) == static_cast<int>(new_c) - 1
                                                                        || static_cast<int>(old_c) == static_cast<int>(new_c) + 1)){
        
            if (colour == 'W'){
            
                // check my colour
                throw InvalidMove{};
            } else {
                char new_colour = theGrid.at(new_r).at(static_cast<int>(new_c))->get_colour();
            
                if (new_colour == 'B'){
                
                    // check new colour
                    throw InvalidMove{};
                } else if (theGrid.at(new_r).at(static_cast<int>(new_c)) == nullptr) {
                
                    // check new piece
                    throw InvalidMove{};
                } else {
                
                    // move and set alive
                    theGrid.at(new_r).at(static_cast<int>(new_c))->set_alive(false);
                    theGrid.at(old_r).at(static_cast<int>(old_c)).swap(theGrid.at(new_r).at(static_cast<int>(new_c)));
                    theGrid.at(old_r).at(static_cast<int>(old_c)).reset();
    			    theGrid.at(old_r).at(static_cast<int>(old_c)) = nullptr;
                }
            }  
        
        } else { 
            
            
                
            bool validmove = theGrid.at(old_r).at(static_cast<int>(old_c))->valid(new_c, 8 - new_r);
            if (!validmove){
                throw InvalidMove{};
            } else {
                bool block = is_block(old_c, old_r, new_c, new_r, colour);
                if (block){
                    throw InvalidMove{};
                } else {
                    
                    isenpassant(old_c, old_r, new_c, new_r);
                    
                if (ispawn == 'P') {
                    if ((old_r == new_r + 1) && (static_cast<int>(old_c) == static_cast<int>(new_c))) {
                        if (theGrid.at(new_r).at(static_cast<int>(new_c)) != nullptr) throw InvalidMove{};//a pawn want to move
                    }
                } 
                if (ispawn == 'p') {
                    if ((old_r == new_r - 1) && (static_cast<int>(old_c) == static_cast<int>(new_c))) {
                        if (theGrid.at(new_r).at(static_cast<int>(new_c)) != nullptr) throw InvalidMove{};//a pawn want to move
                    }
                }
                    
                    
                    //check is that valid
                    theGrid.at(old_r).at(static_cast<int>(old_c)).swap(theGrid.at(new_r).at(static_cast<int>(new_c)));
                   
                    std::shared_ptr<Chess> temp = theGrid.at(old_r).at(static_cast<int>(old_c));
                    
                    // set alive false
                    if (theGrid.at(old_r).at(static_cast<int>(old_c)) != nullptr){     //////////
                        theGrid.at(old_r).at(static_cast<int>(old_c))->set_alive(false);  ////////////
                    } 
                    
                    theGrid.at(old_r).at(static_cast<int>(old_c)).reset();
                    theGrid.at(old_r).at(static_cast<int>(old_c)) = nullptr;            
                    
                    if (colour == 'W'){
                      bool check1 = ischeck('W');
                      if (check1){
                        theGrid.at(old_r).at(static_cast<int>(old_c)).swap(theGrid.at(new_r).at(static_cast<int>(new_c)));
                        theGrid.at(new_r).at(static_cast<int>(new_c)) = temp;
                        
                        // set alive true
                        if (theGrid.at(new_r).at(static_cast<int>(new_c)) != nullptr){    //////////
                            theGrid.at(new_r).at(static_cast<int>(new_c))->set_alive(true); ////////
                        }  //////
                        
                        temp.reset();
                        throw InvalidMove{};
                      }
                    } else {
                      bool check2 = ischeck('B');  
                      if (check2){
                        theGrid.at(old_r).at(static_cast<int>(old_c)).swap(theGrid.at(new_r).at(static_cast<int>(new_c)));
                        theGrid.at(new_r).at(static_cast<int>(new_c)) = temp;
                        
                        // set alive true
                        if (theGrid.at(new_r).at(static_cast<int>(new_c)) != nullptr){    //////////
                            theGrid.at(new_r).at(static_cast<int>(new_c))->set_alive(true); ////////
                        }  //////
                        
                        temp.reset();
                        throw InvalidMove{};
                      }
                    }
                    temp.reset();
                   
                if (ispawn == 'P') {
                    if (((old_r == new_r + 1) && (static_cast<int>(old_c) == static_cast<int>(new_c))) ||
                                      ((old_r == new_r + 2) && (static_cast<int>(old_c) == static_cast<int>(new_c)))){
                        
                         std::shared_ptr<Pawn> p = std::static_pointer_cast<Pawn>(theGrid.at(new_r).at(static_cast<int>(new_c)));
                         if (p->get_first()) p->set_first(false);
                         
                }
                  } 
                if (ispawn == 'p') {
                    if (((old_r == new_r - 1) && (static_cast<int>(old_c) == static_cast<int>(new_c)))
                                      || ((old_r == new_r - 1) && (static_cast<int>(old_c) == static_cast<int>(new_c)))){
                        
                        std::shared_ptr<Pawn> p = std::static_pointer_cast<Pawn>(theGrid.at(new_r).at(static_cast<int>(new_c)));
                         if (p->get_first()) p->set_first(false);
                         
                    }
                 } 
                    
                    
                }
            }
        }
        
        
        
        // set new pos
        theGrid.at(new_r).at(static_cast<int>(new_c))->new_pos(new_c, 8 - new_r);
    
        
        // notify td and gd
        char type = theGrid.at(new_r).at(static_cast<int>(new_c))->get_name();
        
        
        // bool upper = isupper(type);
        if ((old_r % 2 == 0 && static_cast<int>(old_c) % 2 == 0) || (old_r % 2 != 0 && static_cast<int>(old_c) % 2 != 0)){
           td->notify(8 - old_r, old_c, ' ');
          // std::static_pointer_cast<GraphicsDisplay>(gd)->reset_gd(std::static_pointer_cast<TextDisplay>(td));
           gd->notify(8 - old_r, old_c, ' ');
        } else {
           td->notify(8 - old_r, old_c, '_');
         //  std::static_pointer_cast<GraphicsDisplay>(gd)->reset_gd(std::static_pointer_cast<TextDisplay>(td));
           gd->notify(8 - old_r, old_c, '_');
        }
        td->notify(8 - new_r, new_c, type);
      //  std::static_pointer_cast<GraphicsDisplay>(gd)->reset_gd(std::static_pointer_cast<TextDisplay>(td));
        gd->notify(8 - new_r, new_c, type);
    }
}
