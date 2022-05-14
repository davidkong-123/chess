#include "grid.h"
#include "pawn.h"
#include <memory>
#include <stdlib.h>
#include "chess.h"

bool Grid::hasvalidmove(X col, int row, char colour){
    for (int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            // check nullptr
            if (theGrid.at(i).at(j) != nullptr){
                
                // check colour
                if (theGrid.at(i).at(j)->get_colour() != colour){
                    
                    // check pawn attack
                    char type = theGrid.at(row).at(static_cast<int>(col))->get_name();
                    if (colour == 'B' && type == 'P' && (row == i - 1) && (static_cast<int>(col) == j - 1 ||
                        static_cast<int>(col) == j + 1)){ // black attack white
                        
                        // check is check
                        theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                   
                        std::shared_ptr<Chess> temp = theGrid.at(row).at(static_cast<int>(col));
                        theGrid.at(row).at(static_cast<int>(col)).reset();
                        theGrid.at(row).at(static_cast<int>(col)) = nullptr;            
                            
                            
                        bool check1 = ischeck('B');  
                        if (!check1){
                            theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                            theGrid.at(i).at(j) = temp;
                            temp.reset();
                            return true;
                        }
                        
                        
                    } else if (colour == 'W' && type == 'p' && (row == i + 1) && (static_cast<int>(col) == j - 1 ||
                      static_cast<int>(col) == j + 1)) { // white attack black
                          
                        // check is check
                        theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                   
                        std::shared_ptr<Chess> temp = theGrid.at(row).at(static_cast<int>(col));
                        theGrid.at(row).at(static_cast<int>(col)).reset();
                        theGrid.at(row).at(static_cast<int>(col)) = nullptr;            
                            
                            
                        bool check2 = ischeck('W');  
                        if (!check2){
                            theGrid.at(row).at(static_cast<int>(col)).swap(theGrid.at(i).at(j));
                            theGrid.at(i).at(j) = temp;
                            temp.reset();
                            return true;
                        }
                        
                    }
                    
                    // check valid move
                    bool valid1 = theGrid.at(row).at(static_cast<int>(col))->valid(static_cast<X>(j), 8 - i);
                    
                    if (valid1){
                        bool block1 = is_block(static_cast<X>(j), i, col, row, 'W');
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
                    castle_move(colour);
                    if (colour == 'W'){
                        bool check6 = ischeck('W');
                        
                        if (check6 == false) {
                            
                            theGrid.at(7).at(static_cast<int>(4)).swap(theGrid.at(7).at(static_cast<int>(6)));
                            theGrid.at(7).at(static_cast<int>(4))->new_pos(X::e, 1);
                            theGrid.at(7).at(static_cast<int>(5)).swap(theGrid.at(7).at(static_cast<int>(7)));
                            theGrid.at(7).at(static_cast<int>(7))->new_pos(X::h, 1);
                            return true;
                        }
                        
                    } else {
                        bool check7 = ischeck('B');
                                 
                        if (check7 == false) {
                            theGrid.at(0).at(static_cast<int>(4)).swap(theGrid.at(0).at(static_cast<int>(6)));
                            theGrid.at(0).at(static_cast<int>(4))->new_pos(X::e, 8);
                            theGrid.at(0).at(static_cast<int>(5)).swap(theGrid.at(0).at(static_cast<int>(7)));
                            theGrid.at(0).at(static_cast<int>(7))->new_pos(X::h, 8);
                            return true;
                        }
                        
                    }
                    
                }
                
                
                // check valid move
                bool valid2 = theGrid.at(row).at(static_cast<int>(col))->valid(static_cast<X>(j), 8 - i);
                    
                    if (valid2){
                        bool block2 = is_block(static_cast<X>(j), i, col, row, 'W');
                        if (!block2){
                            
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
                            
                                  
                        }
                    } 
            }
        }
    }
    return false;
}


bool Grid::isstalemate(char colour){
    
    // check stalemate
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            
            // check nullptr
            if (theGrid.at(i).at(j) == nullptr) continue;
            
            if(theGrid.at(i).at(j)->get_colour() == colour){
               bool move = hasvalidmove(static_cast<X>(j), i, colour);
               if (move) return true;
            }
            
        }
    }
    
    return  false;
    
}