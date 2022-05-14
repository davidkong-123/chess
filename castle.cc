#include "grid.h"

bool Grid::castling(X old_c, int old_r, X new_c, int new_r, char colour) {
     if ((old_c == X::e && old_r == 7 && new_c == X::g && new_r == 7) ||//king right bot
         (old_c == X::h && old_r == 7 && new_c == X::f && new_r == 7) ||//rook left bot
         (old_c == X::e && old_r == 7 && new_c == X::c && new_r == 7) ||//king left bot
         (old_c == X::a && old_r == 7 && new_c == X::d && new_r == 7) ||//rook right bot
         (old_c == X::e && old_r == 0 && new_c == X::g && new_r == 0) ||//king right top
         (old_c == X::h && old_r == 0 && new_c == X::f && new_r == 0) ||//rook left top
         (old_c == X::e && old_r == 0 && new_c == X::c && new_r == 0) ||//king left top
         (old_c == X::a && old_r == 0 && new_c == X::d && new_r == 0)) {//rook right top
       
      
       if (colour == 'W') {
         if ((old_c == X::e && old_r == 7 && new_c == X::g && new_r == 7) ||//king right bot or rook left bot
             (old_c == X::h && old_r == 7 && new_c == X::f && new_r == 7)) {
                if (theGrid.at(7).at(5) != nullptr) return false;
                if (theGrid.at(7).at(6) != nullptr) return false;
                if (theGrid.at(7).at(4) == nullptr) return false;
                if (theGrid.at(7).at(7) == nullptr) return false;
                if (theGrid.at(7).at(4)->get_name() != 'K') return false;
                if (theGrid.at(7).at(7)->get_name() != 'R') return false;
               
                std::shared_ptr<King> k = std::static_pointer_cast<King>(theGrid.at(7).at(4));
                std::shared_ptr<Rook> r = std::static_pointer_cast<Rook>(theGrid.at(7).at(7));
                if (!k->get_first()) return false;
                if (!r->get_first()) return false;
                
                return true;  
         } else {//king left bot or rook right bot
         
                if (theGrid.at(7).at(1) != nullptr) return false;
                if (theGrid.at(7).at(2) != nullptr) return false;
                if (theGrid.at(7).at(3) != nullptr) return false;
                if (theGrid.at(7).at(0) == nullptr) return false;
                if (theGrid.at(7).at(4) == nullptr) return false;
                if (theGrid.at(7).at(4)->get_name() != 'K') return false;
                if (theGrid.at(7).at(0)->get_name() != 'R') return false;
               
                std::shared_ptr<King> k = std::static_pointer_cast<King>(theGrid.at(7).at(4));
                std::shared_ptr<Rook> r = std::static_pointer_cast<Rook>(theGrid.at(7).at(0));
                if (!k->get_first()) return false;
                if (!r->get_first()) return false;
                
                return true; 
             
         } 
       }
     
        if (colour == 'B') {
            if ((old_c == X::e && old_r == 0 && new_c == X::g && new_r == 0) ||//king right top
                     (old_c == X::h && old_r == 0 && new_c == X::f && new_r == 0)) { //rook left top
            
                 if (theGrid.at(0).at(5) != nullptr) return false;
                 if (theGrid.at(0).at(6) != nullptr) return false;
                 if (theGrid.at(0).at(4) == nullptr) return false;
                 if (theGrid.at(0).at(7) == nullptr) return false;
                 if (theGrid.at(0).at(4)->get_name() != 'k') return false;
                 if (theGrid.at(0).at(7)->get_name() != 'r') return false;
               
                std::shared_ptr<King> k = std::static_pointer_cast<King>(theGrid.at(0).at(4));
                std::shared_ptr<Rook> r = std::static_pointer_cast<Rook>(theGrid.at(0).at(7));
                if (!k->get_first()) return false;
                if (!r->get_first()) return false;
                
                return true;     
            } else {
                 if (theGrid.at(0).at(1) != nullptr) return false;
                 if (theGrid.at(0).at(2) != nullptr) return false;
                 if (theGrid.at(0).at(3) != nullptr) return false;
                 if (theGrid.at(0).at(0) == nullptr) return false;
                 if (theGrid.at(0).at(4) == nullptr) return false;
                 if (theGrid.at(0).at(4)->get_name() != 'k') return false;
                 if (theGrid.at(0).at(0)->get_name() != 'r') return false;
               
                std::shared_ptr<King> k = std::static_pointer_cast<King>(theGrid.at(0).at(4));
                std::shared_ptr<Rook> r = std::static_pointer_cast<Rook>(theGrid.at(0).at(0));
                if (!k->get_first()) return false;
                if (!r->get_first()) return false;
                
                return true; 
                
            }
        }
     
       return false;
    } else {
               return false;
   }
}


void Grid::castle_move(char colour, X new_c) {
    if (colour =='W') {
        if (new_c == X::g || new_c == X::f) {//king right bot && rook left bot
            theGrid.at(7).at(4).swap(theGrid.at(7).at(6));
            theGrid.at(7).at(6)->new_pos(X::g, 1);
            theGrid.at(7).at(7).swap(theGrid.at(7).at(5));
            theGrid.at(7).at(5)->new_pos(X::f, 1);
            td->notify(1,X::g,'K');
            td->notify(1,X::f,'R');
            td->notify(1,X::h,' ');
            td->notify(1,X::e,'_');
           gd->notify(1,X::g,'K');
            gd->notify(1,X::f,'R');
            gd->notify(1,X::h,' ');
            gd->notify(1,X::e,'_');
        } else {//king left bot && rook right bot
            theGrid.at(7).at(4).swap(theGrid.at(7).at(2));
            theGrid.at(7).at(2)->new_pos(X::c, 1);
            theGrid.at(7).at(0).swap(theGrid.at(7).at(3));
            theGrid.at(7).at(3)->new_pos(X::d, 1);
            td->notify(1,X::c,'K');
            td->notify(1,X::d,'R');
            td->notify(1,X::a,'_');
            td->notify(1,X::e,'_');
            gd->notify(1,X::c,'K');
            gd->notify(1,X::d,'R');
            gd->notify(1,X::a,' ');
            gd->notify(1,X::e,'_');
        }
    } else { 
        if (new_c == X::g || new_c == X::f) {//king right top && rook left top
            theGrid.at(0).at(4).swap(theGrid.at(0).at(6));
            theGrid.at(0).at(6)->new_pos(X::g, 8);
            theGrid.at(0).at(7).swap(theGrid.at(0).at(5));
            theGrid.at(0).at(static_cast<int>(5))->new_pos(X::f, 8);
            td->notify(8,X::g,'k');
            td->notify(8,X::f,'r');
            td->notify(8,X::e,' ');
            td->notify(8,X::h,'_');
            gd->notify(8,X::g,'k');
            gd->notify(8,X::f,'r');
            gd->notify(8,X::e,' ');
            gd->notify(8,X::h,'_');
        } else {
            theGrid.at(0).at(4).swap(theGrid.at(0).at(2));
            theGrid.at(0).at(2)->new_pos(X::c, 8);
            theGrid.at(0).at(0).swap(theGrid.at(0).at(3));
            theGrid.at(0).at(3)->new_pos(X::d, 8);
            td->notify(8,X::c,'k');
            td->notify(8,X::d,'r');
            td->notify(8,X::a,'_');
            td->notify(8,X::e,'_');
            gd->notify(8,X::c,'k');
            gd->notify(8,X::d,'r');
            gd->notify(8,X::a,' ');
            gd->notify(8,X::e,' ');
            
        }
        
    }   
    
}