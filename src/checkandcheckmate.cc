#include "grid.h"
#include <iostream>

// Checkmate
bool Grid::ischeckmate(char colour) {
    std::shared_ptr<Chess> king = nullptr;
    std::shared_ptr<Chess> attacker = nullptr;
    int old_r;
    int old_c;
    
    int k_row;
    X k_col;
    
    int a_row;
    X a_col;
    
    //checks for white;
    if (colour == 'W') {
        
        // Gets the White King & its positions. 
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (theGrid.at(i).at(j) == nullptr) continue;
                if (theGrid.at(i).at(j)->get_name() == 'K') {
                    king = theGrid.at(i).at(j);
                    old_r = i;
                    old_c = j;
                    
                    k_row = 8-i;
                    k_col = static_cast<X>(j);
                    break;
                }
            }
            if (king != nullptr) break;
        }
        
        // Checks if your own pieces can block the way. 
        // Find attacker. 
        
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                std::shared_ptr<Chess> piece = theGrid.at(i).at(j);
                if (piece == nullptr) continue;
                if (!(isupper(piece->get_name())) && (piece->get_name() != 'p')) {
                    
                    bool if_valid = piece->valid(k_col, k_row);
                    if (!if_valid) {
                        continue;
                    } else {
                        bool block = is_block(static_cast<X>(j), i, k_col, 8-k_row, 'B');
                        if (block) {
                            continue;
                        } else {
                            attacker = piece;
                            a_row = 8-i;
                            a_col = static_cast<X>(j);
                            break;
                        }
                    }
                }
            }
            if (attacker != nullptr) break;
        }
        
        // Checks if the attacker piece is a pawn. 
        if ((7-k_row > 0) && (7-k_row < 8) && (static_cast<int>(k_col) - 1 > 0) && (static_cast<int>(k_col) + 1 < 8)) {
        if (theGrid.at(7-k_row).at(static_cast<int>(k_col) - 1) != nullptr) {
            if (theGrid.at(7-k_row).at(static_cast<int>(k_col)-1)->get_name() == 'p') {
                attacker = theGrid.at(7-k_row).at(static_cast<int>(k_col)-1);
                a_row = 8-(7-k_row);
                a_col = static_cast<X>(static_cast<int>(k_col) - 1);
            }
        }
        if (theGrid.at(7-k_row).at(static_cast<int>(k_col) + 1) != nullptr) {
            if (theGrid.at(7-k_row).at(static_cast<int>(k_col) + 1)->get_name() == 'p') {
                attacker = theGrid.at(7-k_row).at(static_cast<int>(k_col) + 1);
                a_row = 8-(7-k_row);
                a_col = static_cast<X>(static_cast<int>(k_col) + 1);
            }
        }
        }
        
        // Separately checks if any pawns can eat the attacker. 
        if ((9-a_row > 0) && (9 - a_row < 8) && (static_cast<int>(a_col) - 1 > 0) && (static_cast<int>(a_col) + 1 < 8)) {
        if (theGrid.at(9-a_row).at(static_cast<int>(a_col) - 1) != nullptr) {
            if (theGrid.at(9-a_row).at(static_cast<int>(a_col)-1)->get_name() == 'P') return true;
        }
        if (theGrid.at(9-a_row).at(static_cast<int>(a_col) + 1) != nullptr) {
            if (theGrid.at(9-a_row).at(static_cast<int>(a_col)+1)->get_name() == 'P') return true;
        }
        }
        
        int s_row;
        X s_col;
        
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                std::shared_ptr<Chess> saver = theGrid.at(i).at(j);
                s_row = 8-i;
                s_col = static_cast<X>(j);
                
                if (saver == nullptr) continue;
                if ((s_row == k_row) && (s_col == k_col)) continue;
                
                if (isupper(saver->get_name())) {
                
                // if any white pieces can eat the attacker. 
                    if (saver->get_name() != 'P') {
                        bool if_valid = saver->valid(a_col, a_row);
                        if (if_valid) {
                            bool block = is_block(s_col, 8-s_row, a_col, 8-a_row, 'W');
                            if (!block) return false;
                        }
                    }
                
                // if any white pieces can move to the spaces in between.
                    if (!(attacker->get_name() == 'q' || attacker->get_name() == 'b' || attacker->get_name() == 'r')) continue;
                    
                    if ((a_col == k_col) && (a_row > k_row)) {
                        for (int i = k_row + 1; i <= a_row - 1; ++i) {
                            bool if_valid = saver->valid(k_col, i); 
                            if (if_valid) {
                                bool block = is_block(s_col, 8-s_row, a_col, 8-i, 'W');
                                if (block) {
                                    continue;
                                } else {
                                    return false;
                                }
                            }
                        }
                    } else if (a_col == k_col) {
                        for (int i = k_row - 1; i >= a_row + 1; --i) {
                            bool if_valid = saver->valid(k_col, i); 
                            if (!if_valid) {
                                continue;
                            } else {
                                bool block = is_block(s_col, 8-s_row, a_col, 8-i, 'W');
                                if (block) {
                                    continue;
                                } else {
                                    return false;
                                }
                            }
                        }
                    } else if ((k_row == a_row) && (static_cast<int>(a_col) < static_cast<int>(k_col))) {
                        for (int i = static_cast<int>(a_col) + 1; i <= static_cast<int>(k_col) - 1; ++i) {
                            bool if_valid = saver->valid(static_cast<X>(i), k_row);
                            if (!if_valid) {
                                continue;
                            } else {
                                bool block = is_block(s_col, 8-s_row, static_cast<X>(i), 8 - k_row, 'W');
                                if (block) {
                                    continue;
                                } else {
                                    return false;
                                }
                            }
                        }
                    } else if (k_row == a_row) {
                        for (int i = static_cast<int>(a_col) - 1; i >= static_cast<int>(k_col) + 1; --i) {
                            bool if_valid = saver->valid(static_cast<X>(i), k_row);
                            if (!if_valid) {
                                continue;
                            } else {
                                bool block = is_block(s_col, 8-s_row, static_cast<X>(i), 8 - k_row, 'W');
                                if (block) {
                                    continue;
                                } else {
                                    return false;
                                }
                            }
                        }
                    } else if ((a_row < k_row) && (static_cast<int>(a_col) < static_cast<int>(k_col))) {
                        for(int i = static_cast<int>(a_col) + 1, j = a_row + 1; i <= static_cast<int>(k_col) - 1 && j <= k_row - 1; ++i, ++j) {
                            bool if_valid = saver->valid(static_cast<X>(i), j);
                                if (!if_valid) {
                                    continue;
                                } else {
                                    bool block = is_block(s_col, 8-s_row, static_cast<X>(i), j, 'W');
                                    if (block) {
                                        continue;
                                    } else {
                                        return false;
                                    }
                                }
                        }
                    } else if (a_row < k_row) {
                        for(int i = static_cast<int>(a_col) - 1, j = a_row + 1; i >= static_cast<int>(k_col) + 1 && j <= k_row - 1; --i, ++j) {
                            bool if_valid = saver->valid(static_cast<X>(i), j);
                                if (!if_valid) {
                                    continue;
                                } else {
                                    bool block = is_block(s_col, 8-s_row, static_cast<X>(i), j, 'W');
                                    if (block) {
                                        continue;
                                    } else {
                                        return false;
                                    }
                                }
                        }
                    } else if ((a_row > k_row) && (static_cast<int>(a_col) > static_cast<int>(k_col))) {
                        for (int i = static_cast<int>(a_col) - 1, j = a_row - 1; i >= static_cast<int>(k_col) + 1 && j >= k_row + 1; --i, --j) {
                            bool if_valid = saver->valid(static_cast<X>(i), j);
                                if (!if_valid) {
                                    continue;
                                } else {
                                    bool block = is_block(s_col, 8-s_row, static_cast<X>(i), j, 'W');
                                    if (block) {
                                        continue;
                                    } else {
                                        return false;
                                    }
                                }
                        }
                    } else {
                        for (int i = static_cast<int>(a_col) + 1, j = a_row - 1; i <= static_cast<int>(k_col) - 1 && j >= k_row + 1; ++i, --j)  {
                        bool if_valid = saver->valid(static_cast<X>(i), j);
                            if (!if_valid) {
                                continue;
                            } else {
                                bool block = is_block(s_col, 8-s_row,static_cast<X>(i), j, 'W');
                                if (block) {
                                    continue;
                                } else {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        // Checks if the King can move to its surrounding 8 spots. 
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                if (((old_r + i) < 0) || ((old_c + j) < 0)) continue;
                if (((old_r + i) >= 8) || ((old_c + j) >= 8)) continue;
                
                int new_r = old_r + i;
                int new_c = old_c + j;
                
                if ((theGrid.at(new_r).at(new_c) == nullptr) || (isupper(theGrid.at(new_r).at(new_c)->get_name()) == false)) {
                     theGrid.at(old_r).at(old_c).swap(theGrid.at(new_r).at(new_c));
                     std::shared_ptr<Chess> temp = theGrid.at(old_r).at(old_c);
                     theGrid.at(old_r).at(old_c).reset();
                     theGrid.at(old_r).at(old_c) = nullptr; 
                
                    bool check1 = ischeck('W');
                    if (check1 == true) {
                        theGrid.at(old_r).at(old_c).swap(theGrid.at(new_r).at(new_c));
                        theGrid.at(new_r).at(new_c) = temp;
                        temp.reset();
                    } else {
                        theGrid.at(old_r).at(old_c).swap(theGrid.at(new_r).at(new_c));
                        theGrid.at(new_r).at(new_c) = temp;
                        temp.reset();
                        return false;
                    }
                }
            }
        }
        // Checks if all can be done is done. 
        return true;
        
        // Checks for Black. 
    } else {
        
        // Gets the Black King & its positions. 
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (theGrid.at(i).at(j) == nullptr) continue;
                if (theGrid.at(i).at(j)->get_name() == 'k') {
                    king = theGrid.at(i).at(j);
                    old_r = i;
                    old_c = j;
                    
                    k_row = 8-i;
                    k_col = static_cast<X>(j);
                    break;
                }
            }
            if (king != nullptr) break;
        }
        
        // Checks if your own pieces can block the way. 
        // Find attacker. 
        
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                std::shared_ptr<Chess> piece = theGrid.at(i).at(j);
                if (piece == nullptr) continue;
                if (isupper(piece->get_name()) && (piece->get_name() != 'P')) {
                    
                    bool if_valid = piece->valid(k_col, k_row);
                    if (!if_valid) {
                        continue;
                    } else {
                        bool block = is_block(static_cast<X>(j), i, k_col, 8-k_row, 'W');
                        if (block) {
                            continue;
                        } else {
                            attacker = piece;
                            a_row = 8-i;
                            a_col = static_cast<X>(j);
                            break;
                        }
                    }
                }
            }
            if (attacker != nullptr) break;
        }
        
        // Checks if the attacker is a pawn. 
        if ((9-k_row > 0) && (9-k_row < 8) && (static_cast<int>(k_col) - 1 > 0) && (static_cast<int>(k_col) + 1 < 8)) {
        if (theGrid.at(9-k_row).at(static_cast<int>(k_col) - 1) != nullptr) {
            if (theGrid.at(9-k_row).at(static_cast<int>(k_col) - 1)->get_name() == 'P') {
                attacker = theGrid.at(9 - k_row).at(static_cast<int>(k_col)-1);
                a_row = 8-(9-k_row);
                a_col = static_cast<X>(static_cast<int>(k_col) - 1);
            }
        }
        if (theGrid.at(9-k_row).at(static_cast<int>(k_col) + 1) != nullptr) {
            if (theGrid.at(9-k_row).at(static_cast<int>(k_col) + 1)->get_name() == 'P') {
                attacker = theGrid.at(9-k_row).at(static_cast<int>(k_col) + 1);
                a_row = 8-(9-k_row);
                a_col = static_cast<X>(static_cast<int>(k_col) + 1);
            }
        }
        }
        
        // Checks if a pawn can eat the attacker. 
        if ((7-a_row > 0) && (7-a_row < 8) && (static_cast<int>(a_col) - 1 > 0) && (static_cast<int>(a_col) + 1 < 8)) {
        if (theGrid.at(7-a_row).at(static_cast<int>(a_col) - 1) != nullptr) {
            if (theGrid.at(7-a_row).at(static_cast<int>(a_col)-1)->get_name() == 'p') {
                return true;
            }
        }
        if (theGrid.at(7-a_row).at(static_cast<int>(a_col) + 1) != nullptr) {
            if (theGrid.at(7-a_row).at(static_cast<int>(a_col)+1)->get_name() == 'p') {
                return true;
            }
        }
        }
        
        int s_row;
        X s_col;
        
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                std::shared_ptr<Chess> saver = theGrid.at(i).at(j);
                s_row = 8-i;
                s_col = static_cast<X>(j);
                
                if (saver == nullptr) continue;
                if ((s_row == k_row) && (s_col == k_col)) continue;
                

                if (!(isupper(saver->get_name()))) {
   
                
                 // if any white pieces can eat the attacker. 
                    if (saver->get_name() != 'p') {

                        bool if_valid = saver->valid(a_col, a_row);
                        if (if_valid) {
                            bool block = is_block(s_col, 8-s_row, a_col, 8-a_row, 'B');
                            if (!block) return false;
                        }
                    }
                
                // if any white pieces can move to the spaces in between.
                    if (!(attacker->get_name() == 'Q' || attacker->get_name() == 'B' || attacker->get_name() == 'R')) continue;
                    

                    
                    if ((a_col == k_col) && (a_row > k_row)) {
                        for (int i = k_row + 1; i <= a_row - 1; ++i) {
                            bool if_valid = saver->valid(k_col, i); 
                            if (if_valid) {
                                bool block = is_block(s_col, 8-s_row, a_col, 8-i, 'B');
                                if (block) {
                                    continue;
                                } else {
                                    return false;
                                }
                            }
                        }
                    } else if (a_col == k_col) {
                        for (int i = k_row - 1; i >= a_row + 1; --i) {
                            bool if_valid = saver->valid(k_col, i); 
                            if (!if_valid) {
                                continue;
                            } else {
                                bool block = is_block(s_col, 8-s_row, a_col, 8-i, 'B');
                                if (block) {
                                    continue;
                                } else {
                                    return false;
                                }
                            }
                        }
                    } else if ((k_row == a_row) && (static_cast<int>(a_col) < static_cast<int>(k_col))) {
                        for (int i = static_cast<int>(a_col) + 1; i <= static_cast<int>(k_col) - 1; ++i) {
                            bool if_valid = saver->valid(static_cast<X>(i), k_row);
                            if (!if_valid) {
                                continue;
                            } else {
                                bool block = is_block(s_col, 8-s_row, static_cast<X>(i), 8 - k_row, 'B');
                                if (block) {
                                    continue;
                                } else {
                                    return false;
                                }
                            }
                        }
                    } else if (k_row == a_row) {
                        for (int i = static_cast<int>(a_col) - 1; i >= static_cast<int>(k_col) + 1; --i) {
                            bool if_valid = saver->valid(static_cast<X>(i), k_row);
                            if (!if_valid) {
                                continue;
                            } else {
                                bool block = is_block(s_col, 8-s_row, static_cast<X>(i), 8 - k_row, 'B');
                                if (block) {
                                    continue;
                                } else {
                                    return false;
                                }
                            }
                        }
                    } else if ((a_row < k_row) && (static_cast<int>(a_col) < static_cast<int>(k_col))) {
                        for(int i = static_cast<int>(a_col) + 1, j = a_row + 1; i <= static_cast<int>(k_col) - 1 && j <= k_row - 1; ++i, ++j) {
                            bool if_valid = saver->valid(static_cast<X>(i), j);
                                if (!if_valid) {
                                    continue;
                                } else {
                                    bool block = is_block(s_col, 8-s_row, static_cast<X>(i), j, 'B');
                                    if (block) {
                                        continue;
                                    } else {
                                        return false;
                                    }
                                }
                        }
                    } else if (a_row < k_row) {
                        for(int i = static_cast<int>(a_col) - 1, j = a_row + 1; i >= static_cast<int>(k_col) + 1 && j <= k_row - 1; --i, ++j) {
                            bool if_valid = saver->valid(static_cast<X>(i), j);
                                if (!if_valid) {
                                    continue;
                                } else {
                                    bool block = is_block(s_col, 8-s_row, static_cast<X>(i), j, 'B');
                                    if (block) {
                                        continue;
                                    } else {
                                        return false;
                                    }
                                }
                        }
                    } else if ((a_row > k_row) && (static_cast<int>(a_col) > static_cast<int>(k_col))) {
                        for (int i = static_cast<int>(a_col) - 1, j = a_row - 1; i >= static_cast<int>(k_col) + 1 && j >= k_row + 1; --i, --j) {
                            bool if_valid = saver->valid(static_cast<X>(i), j);
                                if (!if_valid) {
                                    continue;
                                } else {
                                    bool block = is_block(s_col, 8-s_row, static_cast<X>(i), j, 'B');
                                    if (block) {
                                        continue;
                                    } else {
                                        return false;
                                    }
                                }
                        }
                    } else {
                        for (int i = static_cast<int>(a_col) + 1, j = a_row - 1; i <= static_cast<int>(k_col) - 1 && j >= k_row + 1; ++i, --j)  {
                        bool if_valid = saver->valid(static_cast<X>(i), j);
                            if (!if_valid) {
                                continue;
                            } else {
                                bool block = is_block(s_col, 8-s_row,static_cast<X>(i), j, 'B');
                                if (block) {
                                    continue;
                                } else {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        // Checks if the King can move to its surrounding 8 spots. 
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                if (((old_r + i) < 0) || ((old_c + j) < 0)) continue;
                if (((old_r + i) >= 8) || ((old_c + j) >= 8)) continue;
                
                int new_r = old_r + i;
                int new_c = old_c + j;
                
        
                if ((theGrid.at(new_r).at(new_c) == nullptr) || (isupper(theGrid.at(new_r).at(new_c)->get_name()) == false)) {
                     theGrid.at(old_r).at(old_c).swap(theGrid.at(new_r).at(new_c));
                     std::shared_ptr<Chess> temp = theGrid.at(old_r).at(old_c);
                     theGrid.at(old_r).at(old_c).reset();
                     theGrid.at(old_r).at(old_c) = nullptr; 
                
                    bool check1 = ischeck('B');
                    if (check1 == true) {
                        theGrid.at(old_r).at(old_c).swap(theGrid.at(new_r).at(new_c));
                        theGrid.at(new_r).at(new_c) = temp;
                        temp.reset();
                    } else {
                        theGrid.at(old_r).at(old_c).swap(theGrid.at(new_r).at(new_c));
                        theGrid.at(new_r).at(new_c) = temp;
                        temp.reset();
                        return false;
                    }
                }
            }
        }
        // Checks if all can be done is done. 
        return true;
    }
}

// ischeck. 
bool Grid::ischeck(char colour){
    std::shared_ptr<Chess> king = nullptr;
    
    //checks for white;
    if (colour == 'W') {
        
        int k_row;
        X k_col;
        
        // Gets the White King & its positions. 
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (theGrid.at(i).at(j) == nullptr) continue;
                if (theGrid.at(i).at(j)->get_name() == 'K') {
                    king = theGrid.at(i).at(j);
                    k_row = 8-i;
                    k_col = static_cast<X>(j);
                    break;
                }
            }
            if (king != nullptr) break;
        }
        
        // Separately checks if pawns can check. 
        if ((7-k_row > 0) && (static_cast<int>(k_col) - 1 > 0) && (static_cast<int>(k_col) + 1 < 8)) {
        if (theGrid.at(7-k_row).at(static_cast<int>(k_col) - 1) != nullptr) {
            if (theGrid.at(7-k_row).at(static_cast<int>(k_col) - 1)->get_name() == 'p') return true;
        }
        if (theGrid.at(7-k_row).at(static_cast<int>(k_col) + 1) != nullptr) {
            if (theGrid.at(7-k_row).at(static_cast<int>(k_col) + 1)->get_name() == 'p') return true;
        }
        }
        
        // Recursively loops through all black pieces to see which one can check. 
       for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                std::shared_ptr<Chess> piece = theGrid.at(i).at(j);
                if (piece == nullptr) continue;

                if (!(isupper(piece->get_name())) && (piece->get_name() != 'p')) {
                    
                    bool if_valid = piece->valid(k_col, k_row);
                    if (!if_valid) {
                        continue;
                    } else {
                        bool block = is_block(static_cast<X>(j), i, k_col, 8 - k_row, 'B');
                        if (block) {
                            continue;
                        } else {
                            return true;
                        }
                    }
                    
                }
            }
        }
        return false;
        
    // Checks for Black. 
    } else {
        
        int k_row;
        X k_col;
        
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (theGrid.at(i).at(j) == nullptr) continue;
                if (theGrid.at(i).at(j)->get_name() == 'k') {
                    king = theGrid.at(i).at(j);
                    k_row = 8 - i;
                    k_col = static_cast<X>(j);
                    break;
                }
            }
            if (king != nullptr) break;
        }
        
        // Separately checks if pawns can check.
        if ((9 - k_row < 8) && (static_cast<int>(k_col) - 1 > 0) && (static_cast<int>(k_col) + 1 < 8)) {
        if (theGrid.at(9-k_row).at(static_cast<int>(k_col) - 1) != nullptr) {
            if (theGrid.at(9-k_row).at(static_cast<int>(k_col)-1)->get_name() == 'P') return true;
        }
        if (theGrid.at(9-k_row).at(static_cast<int>(k_col) + 1) != nullptr) {
            if (theGrid.at(9-k_row).at(static_cast<int>(k_col)+1)->get_name() == 'P') return true;
        }
        }
        
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                std::shared_ptr<Chess> piece = theGrid.at(i).at(j);
                if (piece == nullptr) continue;
                if (isupper(piece->get_name()) && (piece->get_name() != 'P')) {
                    
                    bool if_valid = piece->valid(k_col, k_row);
                    if (!if_valid) {
                        continue;
                    } else {
                        bool block = is_block(static_cast<X>(j),  i, k_col, 8 - k_row, 'W');
                        if (block) {
                            continue;
                        } else {
                            return true;
                        }
                    }
                    
                }
            }
        }
        return false;
    }
}