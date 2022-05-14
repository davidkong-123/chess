#ifndef GRA_H
#define GRA_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"
#include <string>
#include <sstream>
#include "textdisplay.h"

class GraphicsDisplay : public Observer {
   int size;
   Xwindow xw;
public:
   GraphicsDisplay();
   virtual void notify(int r, X c, char type) override;
   void reset_gd(std::shared_ptr<TextDisplay> const_td);
   void print_winner(char colour);
};
#endif
