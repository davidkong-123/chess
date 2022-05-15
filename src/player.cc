#include "player.h"
#include "grid.h"
#include "chess.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "pawn.h"
#include "queen.h"
#include "king.h"
#include <random>
#include <iterator>
#include <algorithm>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//ctor 
Player::Player(char colour, int level, bool checkmate, Grid * grid):
                colour(colour), level(level), checkmate(checkmate), grid(grid) {}



void Player::addchess(std::shared_ptr<Chess> newchess){
    mychess.emplace_back(newchess);
}


void Player::setlevel(int newlevel){
    this->level = newlevel;
}

// ischeck
bool Player::ischeck(){
    /*std::vector<std::vector<std::shared_ptr<Chess>>> mygrid = grid->getgrid();
    std::shared_ptr<Chess> king = nullptr;
    //checks for white;
    if (colour == 'W') {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (mygrid.at(i).at(j) == nullptr) continue;
                //if (mygrid.at(i).at(j)->get_name() == 'K') {
                  //  king = mygrid.at(i).at(j);
                //    break;
                //}
            }
            if (king != nullptr) break;
        }
        
       for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                std::shared_ptr<Chess> piece = mygrid.at(i).at(j);
                if (piece == nullptr) continue;
                if (isupper(piece->get_name())) {
                    //bool block = grid->is_block(piece->get_x(), piece->get_y(), king->get_x(), king->get_y(), colour);
                    //bool if_valid = piece->valid(king->get_x(), king->get_y());
                    //if (if_valid && !block) return true;
                }
            }
        }
        return false;
    } else {
        return true;
    }*/
}

// iswhite
bool Player::isWhite(){
  if (colour == 'W'){
     return true;
	} else {
     return false;
	}
}


// move
void Player::human_makemove(X old_x_cor, int old_y_cor, X x_cor, int y_cor) {
    if (colour == 'W') {
        grid->move(old_x_cor, old_y_cor, x_cor, y_cor, 'W'); 
    } else {
        grid->move(old_x_cor, old_y_cor, x_cor, y_cor, 'B');
    }
}


void Player::comp_makemove() {
    //if (level == 1) grid->computer1_move(colour);
    //if (level == 2) grid->computer2_move(colour);
    if (level == 3) grid->computer3_move(colour);
    if (level == 4) grid->computer4_move(colour);
}

// computer1
void Player::comp1_makemove(){
    int size = mychess.size();
    int choice;
    
    srand (time(NULL));
    
    while(true){
        choice = rand() % size;
        
        if (mychess.at(choice)->is_alive() == false) continue;
        
        
        bool valid = grid->hasvalidmove(mychess.at(choice)->get_x(), 8 - mychess.at(choice)->get_y(), mychess.at(choice)->get_colour());
        if (valid){
            grid->findvalidmove(mychess.at(choice), move_candidates); // find valid move for 
            
            srand (time(NULL));
            int move_size = move_candidates.size();
            int target;
            
            //std::default_random_engine generator;
            //std::uniform_int_distribution<int> distribution(0,move_size);
            target = rand() % move_size;
            
            
            // grid->move(mychess.at(choice)->get_x(), 8 - mychess.at(choice)->get_y(), 
            // static_cast<X>(move_candidates.at(target).at(1)), move_candidates.at(target).at(0), mychess.at(choice)->get_colour());
            grid->computer1_move(mychess.at(choice), move_candidates.at(target));
            break;
          
        } else {
            continue;
        }
    }
    move_candidates.clear();
    
}


// computer2
void Player::comp2_makemove(){
    int size = mychess.size();
    
    std::vector<Attack> best_attacks;
    int move_level = 0;
    
    
    srand (time(NULL));
    
    for(int i = 0; i < size; ++i){
        
        
        if (mychess.at(i)->is_alive() == false) continue;
        if (mychess.at(i) == nullptr) continue;
        
        bool valid = grid->hasvalidmove(mychess.at(i)->get_x(), 8 - mychess.at(i)->get_y(), mychess.at(i)->get_colour());
        if (valid){
            grid->findvalidmove(mychess.at(i), move_candidates); // find valid move for 
            
            // search best move
            grid->search_best_move(mychess.at(i), move_candidates, best_attacks, move_level);
            move_candidates.clear();
          
        } else {
            continue;
        }
        move_candidates.clear();
    }
    // generate target
    int move_size = best_attacks.size();
    int target;
            
    target = rand() % move_size;
    std::shared_ptr<Chess> best_attacker = best_attacks.at(target).attacker;
    std::vector<int> best_move;
    best_move.emplace_back(best_attacks.at(target).attack_row);
    best_move.emplace_back(best_attacks.at(target).attack_col);
    
    grid->computer2_move(best_attacker, best_move);
    
    
    
}


// computer3
void Player::comp3_makemove(){
    int size = mychess.size();
    
    std::vector<Attack> best_attacks;
    int move_level = 0;
    int captured_level = 0;
    int iscaptured_level = 0;
    
    srand (time(NULL));
    
    for(int i = 0; i < size; ++i){
        
        
        if (mychess.at(i)->is_alive() == false) continue;
        if (mychess.at(i) == nullptr) continue;
        
        bool valid = grid->hasvalidmove(mychess.at(i)->get_x(), 8 - mychess.at(i)->get_y(), mychess.at(i)->get_colour());
        if (valid){
            grid->findvalidmove(mychess.at(i), move_candidates); // find valid move for 
            
            // search best move
            grid->search_best_move3(mychess.at(i), move_candidates, best_attacks, move_level, captured_level, iscaptured_level);
            move_candidates.clear();
          
        } else {
            continue;
        }
        move_candidates.clear();
    }
    // generate target
    int move_size = best_attacks.size();
    int target;
            
    target = rand() % move_size;
    std::shared_ptr<Chess> best_attacker = best_attacks.at(target).attacker;
    std::vector<int> best_move;
    best_move.emplace_back(best_attacks.at(target).attack_row);
    best_move.emplace_back(best_attacks.at(target).attack_col);
    
    grid->computer2_move(best_attacker, best_move);
    
    
}



int Player::get_level(){
    return level;
}

