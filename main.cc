#include <iostream>
#include <string>
#include "grid.h"
#include "state.h"
#include "info.h"
#include "textdisplay.h"
#include "chess.h"
#include "observer.h"
#include "player.h"
#include <memory>
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include <sstream>
#include <stdlib.h>
#include "GraphicsDisplay.h"
#include "window.h"

using namespace std;

// Do not remove any code; do not add code other than where indicated.

void getChars(char & col, char & row, string pos){
  istringstream ss{pos};
	ss >> col;
	ss >> row;
}

X getCol(char col){
   if (col == 'a'){
       return X::a; 
   } else if (col == 'b'){
       return X::b;
   } else if (col == 'c'){
       return X::c;
   } else if (col == 'd'){
       return X::d;
   } else if (col == 'e'){
       return X::e;
   } else if (col == 'f'){
       return X::f;
   } else if (col == 'g'){
       return X::g;
   } else{
       return X::h;
   }
}

int getRow(char row){
    stringstream ss;
    ss << row;
    int i;
    ss >> i;
    return i;
}

// Main function. 
int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  
  Grid g;
  shared_ptr<TextDisplay> td = make_shared<TextDisplay>();
  //shared_ptr<GraphicsDisplay> gd = make_shared<GraphicsDisplay>();
  g.addtd(td); 
//  g.addgd(gd);
  

  // Add code here
  bool white = true;
  bool start = false;
  int white_score = 0;
  int black_score = 0;
  
  // init players
  Grid * ob1 = &g;
  Grid * ob2 = &g;
  Player player1 = Player{'W', 0, false, ob1};
  Player player2 = Player{'B', 0, false, ob2};

  try {
  while (true) {
    cin >> cmd;
       //try{
        if (cmd == "game" && start == false) {
          try{
    
          start = true;
          
          string player1_name;
          string player2_name;
          
          cin >> player1_name;
          cin >> player2_name;
          
          // level 
          if (player1_name == "human"){
            
          } else {
             if (player1_name == "computer1"){
                  player1 = Player{'W', 1, false, ob2};
              } else if (player1_name == "computer2") {
                  player1 = Player{'W', 2, false, ob2};
              } else if (player1_name == "computer3") {
                  player1 = Player{'W', 3, false, ob2};
              }
          }
          
          if (player2_name == "human"){
            
          } else {
              if (player2_name == "computer1"){
                  player2 = Player{'B', 1, false, ob2};
              } else if (player2_name == "computer2"){
                  player2 = Player{'B', 2, false, ob2};
              } else if (player2_name == "computer3"){
                  player2 = Player{'B', 2, false, ob2};
              }
          }
          
          // clear the old grid
            td->reset_td();
            //gd->reset_gd();
            g.clear();
          
          
          std::vector<std::vector<std::shared_ptr<Chess>>> newGrid;
          for(int i = 0; i < 8; ++i){
          std::vector<std::shared_ptr<Chess>> arr;
    
    			   if (i == 0){
    			         shared_ptr<Rook> c1 = std::make_shared<Rook>('r', X::a, 8, true, 'B', true);
    					 arr.emplace_back(c1);
    					 player2.addchess(c1);
    					 
    					 shared_ptr<Knight> c2 = std::make_shared<Knight>('n', X::b, 8, true, 'B');
                         arr.emplace_back(c2);
                         player2.addchess(c2);
                         
                         shared_ptr<Bishop> c3 = std::make_shared<Bishop>('b', X::c, 8, true, 'B');
    				     arr.emplace_back(c3);
    				     player2.addchess(c3);
    				     
    				     shared_ptr<Queen> c4 = std::make_shared<Queen>('q', X::d, 8, true, 'B');
    				     arr.emplace_back(c4);
    				     player2.addchess(c4);
    				     
    				     shared_ptr<King> c5 = std::make_shared<King>('k', X::e, 8, true, 'B', true);
                         arr.emplace_back(c5);
                         player2.addchess(c5);
                         
                         shared_ptr<Bishop> c6 = std::make_shared<Bishop>('b', X::f, 8, true, 'B');
                         arr.emplace_back(c6);
                         player2.addchess(c6);
                         
                         shared_ptr<Knight> c7 = std::make_shared<Knight>('n', X::g, 8, true, 'B');
    					 arr.emplace_back(c7);
    					 player2.addchess(c7);
    					 
    					 shared_ptr<Rook> c8 = std::make_shared<Rook>('r', X::h, 8, true, 'B', true);
    					 arr.emplace_back(c8);
    					 player2.addchess(c8);
    					 
    				 } else if (i == 1){
    				     
    				     shared_ptr<Pawn> c1 = std::make_shared<Pawn>('p', X::a, 7, true, 'B', true);
    				     arr.emplace_back(c1);
    				     player2.addchess(c1);
    				     
    				     shared_ptr<Pawn> c2 = std::make_shared<Pawn>('p', X::b, 7, true, 'B', true);
    					 arr.emplace_back(c2);
    					 player2.addchess(c2);
    					 
    					 shared_ptr<Pawn> c3 = std::make_shared<Pawn>('p', X::c, 7, true, 'B', true);
    					 arr.emplace_back(c3);
    					 player2.addchess(c3);
    					 
    					 shared_ptr<Pawn> c4 = std::make_shared<Pawn>('p', X::d, 7, true, 'B', true);
    					 arr.emplace_back(c4);
    					 player2.addchess(c4);
    					 
    					 shared_ptr<Pawn> c5 = std::make_shared<Pawn>('p', X::e, 7, true, 'B', true);
    					 arr.emplace_back(c5);
    					 player2.addchess(c5);
    					 
    					 shared_ptr<Pawn> c6 = std::make_shared<Pawn>('p', X::f, 7, true, 'B', true);
    					 arr.emplace_back(c6);
    					 player2.addchess(c6);
    					 
    					 shared_ptr<Pawn> c7 = std::make_shared<Pawn>('p', X::g, 7, true, 'B', true);
    					 arr.emplace_back(c7);
    					 player2.addchess(c7);
    					 
    					 shared_ptr<Pawn> c8 = std::make_shared<Pawn>('p', X::h, 7, true, 'B', true);
    					 arr.emplace_back(c8);
    					 player2.addchess(c8);
    					 
    				 } else if (i == 6){
    				     
    				     shared_ptr<Pawn> c1 = std::make_shared<Pawn>('P', X::a, 2, true, 'W', true);
    				     arr.emplace_back(c1);
    				     player1.addchess(c1);
    				     
    				     shared_ptr<Pawn> c2 = std::make_shared<Pawn>('P', X::b, 2, true, 'W', true);
    					 arr.emplace_back(c2);
    					 player1.addchess(c2);
    					 
    					 shared_ptr<Pawn> c3 = std::make_shared<Pawn>('P', X::c, 2, true, 'W', true);
    					 arr.emplace_back(c3);
    					 player1.addchess(c3);
    					 
    					 shared_ptr<Pawn> c4 = std::make_shared<Pawn>('P', X::d, 2, true, 'W', true);
    					 arr.emplace_back(c4);
    					 player1.addchess(c4);
    					 
    					 shared_ptr<Pawn> c5 = std::make_shared<Pawn>('P', X::e, 2, true, 'W', true);
    					 arr.emplace_back(c5);
    					 player1.addchess(c5);
    					 
    					 shared_ptr<Pawn> c6 = std::make_shared<Pawn>('P', X::f, 2, true, 'W', true);
    					 arr.emplace_back(c6);
    					 player1.addchess(c6);
    					 
    					 shared_ptr<Pawn> c7 = std::make_shared<Pawn>('P', X::g, 2, true, 'W', true);
    					 arr.emplace_back(c7);
    					 player1.addchess(c7);
    					 
    					 shared_ptr<Pawn> c8 = std::make_shared<Pawn>('P', X::h, 2, true, 'W', true);
    					 arr.emplace_back(c8);
    					 player1.addchess(c8);
    				 } else if (i == 7){
    				     shared_ptr<Rook> c1 = std::make_shared<Rook>('R', X::a, 1, true, 'W', true);
    				     arr.emplace_back(c1);
    				     player1.addchess(c1);
    				     
    				     shared_ptr<Knight> c2 = std::make_shared<Knight>('N', X::b, 1, true, 'W');
    					 arr.emplace_back(c2);
    					 player1.addchess(c2);
    					 
    					 shared_ptr<Bishop> c3 = std::make_shared<Bishop>('B', X::c, 1, true, 'W');
    					 arr.emplace_back(c3);
    					 player1.addchess(c3);
    					 
    					 shared_ptr<Queen> c4 = std::make_shared<Queen>('Q', X::d, 1, true, 'W');
    					 arr.emplace_back(c4);
    					 player1.addchess(c4);
    					 
    					 shared_ptr<King> c5 = std::make_shared<King>('K', X::e, 1, true, 'W', true);
    					 arr.emplace_back(c5);
    					 player1.addchess(c5);
    					 
    					 shared_ptr<Bishop> c6 = std::make_shared<Bishop>('B', X::f, 1, true, 'W');
    					 arr.emplace_back(c6);
    					 player1.addchess(c6);
    					 
    					 shared_ptr<Knight> c7 = std::make_shared<Knight>('N', X::g, 1, true, 'W');
    					 arr.emplace_back(c7);
    					 player1.addchess(c7);
    					 
    					 shared_ptr<Rook> c8 = std::make_shared<Rook>('R', X::h, 1, true, 'W', true);
    					 arr.emplace_back(c8);
    					  player1.addchess(c8);
    				 } else {
    				   arr.emplace_back(nullptr);
    				   arr.emplace_back(nullptr);
    				   arr.emplace_back(nullptr);
    				   arr.emplace_back(nullptr);
    				   arr.emplace_back(nullptr);
    				   arr.emplace_back(nullptr);
    				   arr.emplace_back(nullptr);
    				   arr.emplace_back(nullptr); 
    				 }
         
    		 newGrid.emplace_back(arr);
    	 }
          
          // initialize the game
            g.init(newGrid);
    
    			//prints out the board.
    			cout << *td;
    			
    
          }
          catch (...){
              start = false;
              continue;
          }
          
        } else if (cmd == "resign" && start == true) {
            
          if (white){
            cout << "Black wins!" << endl;
            ++black_score;
          } else {
            cout << "White wins!" << endl;
            ++white_score;
          }
    	  start = false;
    	  
      	} else if (cmd == "undo" && start == true) {
      	    bool success = g.undo();
      	    if (success) cout << *td;
     
      	} else if (cmd == "history" && start == true) {
      	    if (g.getlist().size() == 0) {
      	        cout << "No history moves. " << endl;
      	    } else {
      	        string Cl;
      	        if (white) {
      	            Cl = "Black";
      	        } else {
      	            Cl = "White";
      	        }
      	        for (size_t i = 0; i < g.getlist().size(); ++i) {
      	            std::vector<int> tmp = g.getlist().at(i);
      	            
      	            cout << "Piece Moved: " << Cl << endl;
      	            if (Cl == "Black") {
      	                Cl = "White";
      	            } else {
      	                Cl = "Black";
      	            }
      	            char magic = tmp[0] + 97;
      	            char magic2 = tmp[2] + 97;
      	            cout << "Starting Position: " << magic << 8 - tmp[1] << endl;
      	            cout << "Ending Position: " << magic2 << 8 - tmp[3] << endl;
      	        }
      	    }
      	} else if (cmd == "move" && start == true){
      	   
      	  if (white == false && player2.get_level() == 1){
      	      
      	        player2.comp1_makemove();
      	        
      	  } else if (white == true && player1.get_level() == 1){
      	      
      	        player1.comp1_makemove();
      	  
      	  } else if (white == false && player2.get_level() == 2){
      	    
      	        player2.comp2_makemove();
      	  
      	  } else if (white == true && player1.get_level() == 2){
      	      
      	        player1.comp2_makemove();
      	      
      	  } else if (white == false && player2.get_level() == 3){
      	    
      	        player2.comp3_makemove();
      	  
      	  } else if (white == true && player1.get_level() == 3){
      	      
      	        player1.comp3_makemove();
      	      
      	  } else {
      	    
          	  string old_p;
          	  string new_p;
          	  
          	  cin >> old_p;
          	  if (cin.fail()){
          	     // computer move
          	  } else {
          	      cin >> new_p;
          	      if (cin.fail()){
          	          cout << "The move is invalid, please enter again" << endl;
          	          continue;
          	      } else {
          	          try {
          	              // get new row and col
          	              char new_c_char;
          	              char new_r_char;
          	              getChars(new_c_char,new_r_char,new_p);
          	              X new_c = getCol(new_c_char);
          	              int new_r = 8 - getRow(new_r_char);
          	              
          	              // get old row and col
          	              char old_c_char;
          	              char old_r_char;
          	              getChars(old_c_char,old_r_char,old_p);
          	              X old_c = getCol(old_c_char);
          	              int old_r = 8 - getRow(old_r_char);
          	              
          	              
          	              // human move
          	              if (white == true){
          	                 
          	                 shared_ptr<Chess> temp = (g.getgrid()).at(new_r).at(static_cast<int>(new_c));
          	                 
          	                 g.move(old_c, old_r, new_c, new_r, 'W');
          	                 
          	                 std::vector<int> tmp;
          	                 tmp.emplace_back(static_cast<int>(old_c));
          	                 tmp.emplace_back(old_r);
          	                 tmp.emplace_back(static_cast<int>(new_c));
          	                 tmp.emplace_back(new_r);
          	                 
          	                 if (temp != nullptr) {
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
          	                 
          	                 (g.getlist()).emplace_back(tmp);
          	                 //white = false;
          	                 
          	              } else {
          	                 
          	                 shared_ptr<Chess> temp = (g.getgrid()).at(new_r).at(static_cast<int>(new_c));
          	                 
          	                 g.move(old_c, old_r, new_c, new_r, 'B');
          	                 std::vector<int> tmp;
          	                 tmp.emplace_back(static_cast<int>(old_c));
          	                 tmp.emplace_back(old_r);
          	                 tmp.emplace_back(static_cast<int>(new_c));
          	                 tmp.emplace_back(new_r);
          	                 
          	                 if (temp != nullptr) {
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
          	                 (g.getlist()).emplace_back(tmp);
          	                 
          	                 //white = true;
          	              }
          	              
          	              
          	              // change pawn
                		  
                		  shared_ptr<Chess> & temp = g.getpiece(new_c, new_r);
                		  char oldtype = temp->get_name();
                		 
                		  
                		  if ((oldtype == 'p'  && new_r == 7)|| (oldtype == 'P' && new_r == 0)) {
                		   
                		  //take in the char that represent the new piece	  
                		  
                		  char newtype;
                	      cin >> newtype;
                		  
                		    if (oldtype == 'P' && new_r == 0){
                              if (newtype == 'Q'){
                		              g.setPiece('Q', new_c, 8 - new_r, 'W');
                		          } else if (newtype == 'B'){
                		              g.setPiece('B', new_c, 8 - new_r, 'W');
                		          } else if (newtype == 'N'){
                		              g.setPiece('N', new_c, 8 - new_r, 'W');
                		          } else if (newtype == 'R'){
                		              g.setPiece('R', new_c, 8 - new_r, 'W');
                		          } else {
                		              throw InvalidMove{};
                		          }
                		      } else if (oldtype == 'p' && new_r == 7) {
                		          
                		          if (newtype == 'q'){
                		              g.setPiece('q', new_c,8 - new_r, 'B');
                		          } else if (newtype == 'b'){
                		              g.setPiece('b', new_c,8 - new_r, 'B');
                		          } else if (newtype == 'n'){
                		              g.setPiece('n', new_c, 8 - new_r, 'B');
                		          } else if (newtype == 'r'){
                		              g.setPiece('r', new_c,8 - new_r, 'B');
                		          } else {
                		              throw InvalidMove{};
                		          }
                		      } else {
                		          throw InvalidMove{};
                		      } 
        		            
        		          }
        		          
        
          	          
          	          }
          	          catch(InvalidMove & m){
          	              cout << "The move is invalid, please enter again" << endl;
          	              continue;
          	          }
          	      }
          	  }
      	  }
      	  
      	      if (white){
      	          white = false;
      	      } else {
      	          white = true;
      	      }
      	      
      	      cout << *td;
      	      
     	      if (g.ischeck('W')) {
     	          if (g.ischeckmate('W')) {
     	              cout << "Checkmate! Black wins!" << endl;
     	              ++black_score;
     	              start = false;
     	          } else {
     	               cout << "White is in check." << endl; 
     	          }
     	      }
     	      
     	      if (g.ischeck('B')) {
     	          if (g.ischeckmate('B')) {
     	              cout << "Checkmate! White wins!" << endl;
     	              ++white_score;
     	              start = false;
     	          } else {
     	               cout << "Black is in check." << endl; 
     	          }
     	      }
     	      
     	      if (g.ischeck('W') == false && g.ischeck('B') == false) {
     	          if (white){
     	              if (g.isstalemate('W')){
     	                cout << "Stalemate!" << endl;
     	                start = false;  
     	              }
     	          } else {
     	              if (g.isstalemate('B')){
     	                cout << "Stalemate!" << endl;
     	                start = false;  
     	              }
     	          }
     	      }
      	  
      	} else if (cmd == "setup" && start == true) {
      	    while(true){
      	        try {
      	          string c;
      	          cin >> c;
      	          if (c == "done" ){
      	             bool done = g.checkdone();
      	             if (done){
    					cout << "Exiting setup mode" << endl;
      	                break;
      	             } else {
    					cout << "Failed to exit setup mode" << endl;
      	                continue;
      	             }
      	          } else if (c == "+"){
      	              
      	              // get col and row
      	              char type;
      	              string pos;
      	              cin >> type;
      	              cin >> pos;
      	              char c_col;
      	              char c_row;
      	              getChars(c_col, c_row, pos);
      	              X col;
      	              int row;
      	              col = getCol(c_col);
      	              row = getRow(c_row);
                       
                      // set piece
                      bool upper = isupper(type);
                      if (upper){
                        g.setPiece(type, col, row, 'W'); // grid notify td, gd;
                      } else {
                        g.setPiece(type, col, row, 'B'); // grid notify td, gd;  
                      }
    
    									cout << *td;
      	              
      	          } else if (c == "-"){
      	              string pos;
      	              cin >> pos;
      	              
      	              // get col and row
      	              char c_col;
      	              char c_row;
      	              getChars(c_col, c_row, pos);
      	              X col;
      	              int row;
      	              col = getCol(c_col);
      	              row = getRow(c_row);
      	              
      	              // remove piece
      	                  g.removePiece(col, row);
    				      cout << *td;
    
      	          } else if (c == "="){
      	              string colour;
      	              cin >> colour;
      	               if (colour == "black") {
      	                   white = false;
      	               } else if (colour == "white") {
      	                   white = true;
      	               } else {
      	                  cout << "Please enter either black or white" << endl;
      	                  continue;
      	               }
      	               
      	          } else {
    				continue;
    			  }
    					
      	        }
    			catch(...){
    				continue;
    			}
      	    }
      	    
      	    if ((g.isstalemate('W')) || (g.isstalemate('B'))) cout << "Stalemate!" << endl;
      	    
      	} else {
      	    continue;
      	}
    //} catch (ios::failure &) {
      //  continue;
    //}
   }
   }
   catch (ios::failure &) {} // Any I/O failure quit
  
	// Prints out the score. 
	cout << "Final Score:" << endl;
	cout << "White: " << white_score << endl;
	cout << "Black: " << black_score << endl;
}
