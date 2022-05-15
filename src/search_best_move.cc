void Grid::search_best_move(std::shared_ptr<Chess> c, std::vector<std::vector<int>> & candidates, 
                            std::vector<Attack> & best_attacks, int & move_level){
    
    //int best_col = candidates.at(0).at(1);
    //int best_row = candidates.at(0).at(0);
    
    for(int i = 0; i < candidates.size(); ++i){
        int row = candidates.at(i).at(0);
        int col = candidates.at(i).at(1);
        
        if (theGrid.at(row).at(col) != nullptr){
            
            if (move_level == 0){
                
                if (theGrid.at(row).at(col)->get_name() == 'k' || theGrid.at(row).at(col)->get_name() == 'K'){
                    best_attacks.clear();
                    move_level = 2;
                    best_attacks.emplace_back(Attack{c, row, col});
                } else {
                    best_attacks.clear();
                    move_level = 1;
                    best_attacks.emplace_back(Attack{c, row, col});
                }
                
            } else if (move_level == 1){
                
                if (theGrid.at(row).at(col)->get_name() == 'k' || theGrid.at(row).at(col)->get_name() == 'K'){
                    best_attacks.clear();
                    move_level = 2;
                    best_attacks.emplace_back(Attack{c, row, col});
                } else {
                    best_attacks.emplace_back(Attack{c, row, col});
                }
                
            } else if (move_level == 2) {
                
                if (theGrid.at(row).at(col)->get_name() == 'k' || theGrid.at(row).at(col)->get_name() == 'K'){
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
void Grid::search_best_move3(std::shared_ptr<Chess> c, std::vector<std::vector<int>> & candidates, 
                            std::vector<Attack> & best_attacks, int & move_level, int & captured_level){
                                
    
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
                        
                        if (theGrid.at(row).at(col)->get_name() == 'k' || theGrid.at(row).at(col)->get_name() == 'K'){
                            
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
                        
                        if (theGrid.at(row).at(col)->get_name() == 'k' || theGrid.at(row).at(col)->get_name() == 'K'){
                            best_attacks.clear();
                            move_level = 2;
                            best_attacks.emplace_back(Attack{c, row, col});
                        } else {
                            best_attacks.emplace_back(Attack{c, row, col});
                        }
                        
                    } else if (move_level == 2) {
                        
                        if (theGrid.at(row).at(col)->get_name() == 'k' || theGrid.at(row).at(col)->get_name() == 'K'){
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
                        
                        
                        if (theGrid.at(row).at(col)->get_name() == 'k' || theGrid.at(row).at(col)->get_name() == 'K'){
                            
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
                        
                        if (theGrid.at(row).at(col)->get_name() == 'k' || theGrid.at(row).at(col)->get_name() == 'K'){
                            
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
                        
                        if (theGrid.at(row).at(col)->get_name() == 'k' || theGrid.at(row).at(col)->get_name() == 'K'){
                            best_attacks.clear();
                            move_level = 2;
                            best_attacks.emplace_back(Attack{c, row, col});
                        } else {
                            best_attacks.emplace_back(Attack{c, row, col});
                        }
                        
                    } else if (move_level == 2) {
                        
                        if (theGrid.at(row).at(col)->get_name() == 'k' || theGrid.at(row).at(col)->get_name() == 'K'){
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
                 isenpassant(old_c, old_r, new_c, new_r);
                 if (enpassant){
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





