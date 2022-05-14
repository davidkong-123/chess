#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "chess.h"

class Observer {
 public:
  virtual void notify(int r, X c, char type) = 0;//pass the Subject that called the notify method
  virtual ~Observer() = default;
};
#endif
