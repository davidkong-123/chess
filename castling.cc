#include "grid.h"
#include "king.h"
#include "rook.h"
#include <memory>

bool Grid::castling(X old_c, int old_r, X new_c, int new_r, char colour) {
     if ((old_c == X::e && old_r == 7 && new_c == X::g && new_r == 7) ||
         (old_c == X::h && old_r == 7 && new_c == X::f && new_r == 7) ||
         (old_c == X::e && old_r == 0 && new_c == X::g && new_r == 0) ||
         (old_c == X::h && old_r == 0 && new_c == X::h && new_r == 0)) {
       if (is_block(X::e, 0, X::h, 0, 'B')) return false;
       if (is_block(X::e, 7, X::h, 7, 'W')) return false;
       if (colour == 'W') {
         if (theGrid.at(7).at(4) == nullptr) return false;
         if (theGrid.at(7).at(7) == nullptr) return false;
         if (theGrid.at(7).at(4)->get_name() != 'K') return false;
         if (theGrid.at(7).at(7)->get_name() != 'R') return false;
       
        std::shared_ptr<King> k = std::static_pointer_cast<King>(theGrid.at(7).at(4));
        std::shared_ptr<Rook> r = std::static_pointer_cast<Rook>(theGrid.at(7).at(7));
        if (!k->get_first()) return false;
        if (!r->get_first()) return false;
        
        return true;     
       }
     
       if (colour == 'B') {
         if (theGrid.at(0).at(4) == nullptr) return false;
         if (theGrid.at(0).at(7) == nullptr) return false;
         if (theGrid.at(0).at(4)->get_name() != 'k') return false;
         if (theGrid.at(0).at(7)->get_name() != 'r') return false;
       
        std::shared_ptr<King> k = std::static_pointer_cast<King>(theGrid.at(0).at(4));
        std::shared_ptr<Rook> r = std::static_pointer_cast<Rook>(theGrid.at(0).at(7));
        if (!k->get_first()) return false;
        if (!r->get_first()) return false;
        
        return true;     
      }
     
       return false;
    } else {
               return false;
   }
}

void Grid::castle_move(char colour) {
    if (colour =='W') {
        theGrid.at(7).at(4).swap(theGrid.at(7).at(6));
        theGrid.at(7).at(7).swap(theGrid.at(7).at(5));
        td->notify(1,X::g,'K');
        td->notify(1,X::f,'R');
        td->notify(1,X::h,' ');
        td->notify(1,X::e,'_');
    } else {
        theGrid.at(0).at(4).swap(theGrid.at(0).at(6));
        theGrid.at(0).at(7).swap(theGrid.at(0).at(5));
        td->notify(8,X::g,'k');
        td->notify(8,X::f,'r');
        td->notify(8,X::e,' ');
        td->notify(8,X::h,'_');
        
    }   
    
}