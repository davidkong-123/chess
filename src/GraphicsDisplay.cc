#include "GraphicsDisplay.h"




GraphicsDisplay::GraphicsDisplay() {

    int square = 500 / 8;
//draw the grid
    for (int r = 0;r < 8; ++r) {
     for (int c = 0; c < 8; ++c) {
       if (((0 == c%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == c%2 ))) {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::Silver);
       } else  {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::DarkOliveGreen);
       }
      }
    }
//draw the coord
   for (int r = 1; r < 9; ++r) {
      int a = 9 - r;
      std::stringstream ss;
      ss << a;
      std::string s = ss.str();
      xw.drawString(3, square * (r - 1) + 15, s);
    }

//draw the coord
    for (int r = 1; r < 9; ++r) {
      char a = 96 + r;
      std::stringstream ss;
      ss << a;
      std::string s = ss.str();
      xw.drawString(square * r - 8, 8 * square - 2, s);
    }

    for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                        if (i == 0) {
                                if ((j == 0) || (j == 7)) {
                                        xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"r");
                                } else if ((j == 1) || (j == 6)) {
                                    xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"n");
                                } else if ((j == 2) || (j == 5)) {
                                    xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"b");
                                } else if (j == 3) {
                                    xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"q");
                                } else {
                                    xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"k");
                                }
                        } else if (i == 1) {
                                    xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"p");
                        } else if (i == 6) {
                                    xw.drawString(j * square + square / 3,i * square + square / 2 + 5,"P");
                        } else if (i == 7) {
                                if ((j == 0) || (j == 7)) {
                                        xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"R");
                                } else if ((j == 1) || (j == 6)) {
                                        xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"N");
                                } else if ((j == 2) || (j == 5)) {
                                        xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"B");
                                } else if (j == 3) {
                                    xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"Q");
                                } else {
                                   xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"K");
                                }
                        }  else{
                    continue;
                            }
                }
        }


}

void GraphicsDisplay::print_winner(char colour) {
    if (colour == 'W') {
     xw.drawString(230 , 230, "White win!!") ;
    } else {
     xw.drawString(230 , 230, "Black win!!");   
    }

}

void GraphicsDisplay::notify(int x, X u, char type) {

     int square = 500 / 8;
     int r = 8 - x;
     int c = static_cast<int>(u);
     int s = c;

     
    if (type == 'P') {
        //repaint the grid
        if (((0 == c%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == c%2 ))) {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::Silver);
       } else  {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::DarkOliveGreen);
       }
        
        xw.drawString(c * square + square / 3,r * square + square / 2 + 5,"P");
    
        
    } else if (type == 'p') {
        if (((0 == s%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == s%2 ))) {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::Silver);
       } else  {
          xw.fillRectangle(c * square, r * square, square, square, Xwindow::DarkOliveGreen);
       }
       
        xw.drawString(s * square + square / 3,r * square + square / 2 + 5,"p");
        
    } else if (type == 'K') {
        if (((0 == s%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == s%2 ))) {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::Silver);
       } else  {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::DarkOliveGreen);
       }
       
        xw.drawString(s * square + square / 3,r * square + square / 2 + 5,"K");
        
    } else if (type == 'k') {
        if (((0 == s%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == s%2 ))) {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::Silver);
       } else  {
          xw.fillRectangle(c * square, r * square, square, square, Xwindow::DarkOliveGreen);
       }
       
        xw.drawString(s * square + square / 3,r * square + square / 2 + 5,"k");
        
    } else if (type == 'B') {
        if (((0 == s%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == s%2 ))) {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::Silver);
       } else  {
          xw.fillRectangle(c * square, r * square, square, square, Xwindow::DarkOliveGreen);
       }
       
        xw.drawString(s * square + square / 3,r * square + square / 2 + 5,"B");
        
    } else if (type == 'b') {
        if (((0 == c%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == c%2 ))) {
          xw.fillRectangle(c * square, r * square, square, square, Xwindow::Silver);
       } else  {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::DarkOliveGreen);
       }
       
        xw.drawString(c * square + square / 3,r * square + square / 2 + 5,"b");
        
    } else if (type == 'Q') {
        if (((0 == c%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == c%2 ))) {
          xw.fillRectangle(c * square, r * square, square, square, Xwindow::Silver);
       } else  {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::DarkOliveGreen);
       }
       
        xw.drawString(c * square + square / 3,r * square + square / 2 + 5,"Q");
        
    } else if (type == 'q') {
        if (((0 == c%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == c%2 ))) {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::Silver);
       } else  {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::DarkOliveGreen);
       }
       
        xw.drawString(c * square + square / 3,r * square + square / 2 + 5,"q");
        
    } else if (type == 'N') {
        if (((0 == c%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == c%2 ))) {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::Silver);
       } else  {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::DarkOliveGreen);
       }
       
        xw.drawString(c * square + square / 3,r * square + square / 2 + 5,"N");
        
    } else if (type == 'n') {
        if (((0 == c%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == c%2 ))) {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::Silver);
       } else  {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::DarkOliveGreen);
       }
       
        xw.drawString(c * square + square / 3,r * square + square / 2 + 5,"n");
        
    } else if (type == 'R') {
        if (((0 == c%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == c%2 ))) {
          xw.fillRectangle(c * square, r * square, square, square, Xwindow::Silver);
       } else  {
          xw.fillRectangle(c * square, r * square, square, square, Xwindow::DarkOliveGreen);
       }
       
        xw.drawString(c * square + square / 3,r * square + square / 2 + 5,"R");
        
    } else if (type == 'r') {
        if (((0 == c%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == c%2 ))) {
          xw.fillRectangle(c * square, r * square, square, square, Xwindow::Silver);
       } else  {
          xw.fillRectangle(c * square, r * square, square, square, Xwindow::DarkOliveGreen);
       }
       
        xw.drawString(c * square + square / 3,r * square + square / 2 + 5,"r");
         
    }  else  {
        if (((0 == c%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == c%2 ))) {
          xw.fillRectangle(c * square, r * square, square, square, Xwindow::Silver);
       } else  {
          xw.fillRectangle(c * square, r * square, square, square, Xwindow::DarkOliveGreen);
       }
       
        
    }
    
   
//draw the coord
   for (int r = 1; r < 9; ++r) {
      int a = 9 - r;
      std::stringstream ss;
      ss << a;
      std::string s = ss.str();
      xw.drawString(3, square * (r - 1) + 15, s);
    }
    
//draw the coord
    for (int r = 1; r < 9; ++r) {
      char a = 96 + r;
      std::stringstream ss;
      ss << a;
      std::string s = ss.str();
      xw.drawString(square * r - 8, 8 * square - 2, s);
    }
    
}


void GraphicsDisplay::reset_gd(std::shared_ptr<TextDisplay> const_td){


    int square = 500 / 8;

//draw the grid
    for (int r = 0;r < 8; ++r) {
     for (int c = 0; c < 8; ++c) {
       if (((0 == c%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == c%2 ))) {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::Silver);
       } else  {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::DarkOliveGreen);
       }
      }
    }
//draw the coord
   for (int r = 1; r < 9; ++r) {
      int a = 9 - r;
      std::stringstream ss;
      ss << a;
      std::string s = ss.str();
      xw.drawString(3, square * (r - 1) + 15, s);
    }

//draw the coord
    for (int r = 1; r < 9; ++r) {
      char a = 96 + r;
      std::stringstream ss;
      ss << a;
      std::string s = ss.str();
      xw.drawString(square * r - 8, 8 * square - 2, s);
    }

    for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                       
                                if (const_td->output_char(i,j) == 'r') {
                                        xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"r");
                                } else if (const_td->output_char(i,j) == 'n') {
                                    xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"n");
                                } else if (const_td->output_char(i,j) == 'b') {
                                    xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"b");
                                } else if (const_td->output_char(i,j) == 'q') {
                                    xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"q");
                                } else if (const_td->output_char(i,j) == 'k') {
                                    xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"k");
                                 } else if (const_td->output_char(i,j) == 'p') {
                                    xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"p");
                                } else if (const_td->output_char(i,j) == 'P') {
                                    xw.drawString(j * square + square / 3,i * square + square / 2 + 5,"P");
                                } else if (const_td->output_char(i,j) == 'R') {
                                        xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"R");
                                } else if (const_td->output_char(i,j) == 'N') {
                                        xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"N");
                                } else if (const_td->output_char(i,j) == 'B') {
                                        xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"B");
                                } else if (const_td->output_char(i,j) == 'Q') {
                                    xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"Q");
                                } else if (const_td->output_char(i,j) == 'K'){
                                   xw.drawString(j * square + square / 3 ,i * square + square / 2 + 5,"K");
                                } else{
                                  continue;
                            }
                }
        }

}
