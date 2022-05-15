#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "chess.h"
#include <string>
#include <memory>

class TextDisplay: public Observer {
  std::vector<std::vector<char>> theDisplay;

 public:
  TextDisplay();
  virtual void notify(int r, X c, char type) override;
  void reset_td();
  void make_td(std::shared_ptr<TextDisplay> const_td);
  char output_char(int i, int j);
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
