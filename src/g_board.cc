#include <iostream>
#include "window.h"
#include <sstream>
#include <string>

using namespace std;

int main() {
  Xwindow xw;


  int square = 500 / 8;
  for (int r = 0;r < 8; ++r) {
     for (int c = 0; c < 8; ++c) {
       if (((0 == c%2 ) && (0 == r %2)) || ((1 == r %2 ) && (1 == c%2 ))) {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::Blue);
       } else  {
           xw.fillRectangle(c * square, r * square, square, square, Xwindow::White);
       }
      }
     }

   for (int r = 1; r < 9; ++r) {
      int a = 9 - r;
      stringstream ss;
      ss << a;
      string s = ss.str();
      xw.drawString(3, square * (r - 1) + 15, s);
   }

for (int r = 1; r < 9; ++r) {
      char a = 96 + r;
      stringstream ss;
      ss << a;
      string s = ss.str();
      xw.drawString(square * r - 8, 8 * square - 2, s);
}



  //w.showAvailableFonts();

  char c;
  cin >> c;

}
