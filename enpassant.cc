#include "grid.h"
#include "pawn.h"
#include <memory>
#include <stdlib.h>
#include "chess.h"




void Grid::isenpassant(X old_c, int old_r, X new_c, int new_r){
    
     // check pawn
     if (theGrid.at(old_r).at(static_cast<int>(old_c))->get_name() == 'P' || 
         theGrid.at(old_r).at(static_cast<int>(old_c))->get_name() == 'p'){
           //std::shared_ptr<Pawn> p = std::static_pointer_cast<Pawn>(theGrid.at(old_r).at(static_cast<int>(old_c)));
           
           // check 2 steps move
           if (abs(new_r - old_r == 2)){
               
               bool upper = isupper(theGrid.at(old_r).at(static_cast<int>(old_c))->get_name());
               
               // check captured by other pawn
               if (upper){
                   ep_r = old_r - 1;
                   ep_c = old_c;
                   
                   ep_eat_r = new_r;
                   ep_eat_c = new_c;
                   
                   // check boundaries??
                   if (theGrid.at(ep_r - 1).at(static_cast<int>(ep_c) + 1) != nullptr){
                      if (theGrid.at(ep_r - 1).at(static_cast<int>(ep_c) + 1)->get_name() == 'p'){
                          ep_candidates.emplace_back(theGrid.at(ep_r - 1).at(static_cast<int>(ep_c) + 1)); // add candidates
                          enpassant  =true;  // enpassant!!!
                      }
                   }
                   
                   if (theGrid.at(ep_r - 1).at(static_cast<int>(ep_c) - 1) != nullptr) {
                       if (theGrid.at(ep_r - 1).at(static_cast<int>(ep_c) - 1)->get_name() == 'p'){
                          ep_candidates.emplace_back(theGrid.at(ep_r - 1).at(static_cast<int>(ep_c) - 1)); // add candidates
                          enpassant  =true;  // enpassant!!!
                      }
                   }
                   
                   
               } else {
                   ep_r = old_r + 1;
                   ep_c = old_c;
                   
                   ep_eat_r = new_r;
                   ep_eat_c = new_c;
                   
                   if (theGrid.at(ep_r + 1).at(static_cast<int>(ep_c) + 1) != nullptr){
                      if (theGrid.at(ep_r + 1).at(static_cast<int>(ep_c) + 1)->get_name() == 'P'){
                          ep_candidates.emplace_back(theGrid.at(ep_r + 1).at(static_cast<int>(ep_c) + 1)); // add candidates
                          enpassant  =true;  // enpassant!!!
                      }
                   }
                   
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


bool Grid::enpassant_move(X old_c, int old_r, X new_c, int new_r){
    if (new_c == ep_c && new_r == ep_r){
        for(int i = 0; i < ep_candidates.size(); ++i){
            if (theGrid.at(old_r).at(static_cast<int>(old_c)) == ep_candidates.at(i)){
                
                // enpassant move
                theGrid.at(ep_eat_r).at(static_cast<int>(ep_eat_c)).reset();
                theGrid.at(ep_eat_r).at(static_cast<int>(ep_eat_c)) = nullptr;
                
                theGrid.at(old_r).at(static_cast<int>(old_c)).swap(theGrid.at(new_r).at(static_cast<int>(new_c)));
                theGrid.at(old_r).at(static_cast<int>(old_c)).reset();
			    theGrid.at(old_r).at(static_cast<int>(old_c)) = nullptr;
                
                enpassant = false;
                return true;
            }
        }
    } 
    
      enpassant = false;   
      return false;
}












