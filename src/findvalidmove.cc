#include "grid.h"
#include <memory>

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
                        for(int i = 0; i < ep_candidates.size(); ++i){
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
                    //castle_move(colour);
                    if (colour == 'W'){
                        bool check6 = ischeck('W');
                        
                        if (check6 == false) {
                            
                             // add candidates
                            std::vector<int> v;
                            v.emplace_back(i);
                            v.emplace_back(j);
                            candidates.emplace_back(v);
                            
                        }
                        
                        theGrid.at(7).at(static_cast<int>(4)).swap(theGrid.at(7).at(static_cast<int>(6)));
                        theGrid.at(7).at(static_cast<int>(4))->new_pos(X::e, 1);
                        theGrid.at(7).at(static_cast<int>(5)).swap(theGrid.at(7).at(static_cast<int>(7)));
                        theGrid.at(7).at(static_cast<int>(7))->new_pos(X::h, 1);
                        
                    } else {
                        bool check7 = ischeck('B');
                                 
                        if (check7 == false) {
                            
                            // add candidates
                            std::vector<int> v;
                            v.emplace_back(i);
                            v.emplace_back(j);
                            candidates.emplace_back(v);
                            
                        }
                        theGrid.at(0).at(static_cast<int>(4)).swap(theGrid.at(0).at(static_cast<int>(6)));
                        theGrid.at(0).at(static_cast<int>(4))->new_pos(X::e, 8);
                        theGrid.at(0).at(static_cast<int>(5)).swap(theGrid.at(0).at(static_cast<int>(7)));
                        theGrid.at(0).at(static_cast<int>(7))->new_pos(X::h, 8);
                        
                    }
                    
                }
                
                
                // check valid move
                bool valid2 = theGrid.at(row).at(static_cast<int>(col))->valid(static_cast<X>(j), 8 - i);
                    
                    if (valid2){
                        bool block2 = is_block(col, row, static_cast<X>(j), i, colour);
                        if (!block2){
                            
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
