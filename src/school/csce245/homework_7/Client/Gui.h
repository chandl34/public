#ifndef GUI_H     /* -*- C++ -*- */
#define GUI_H

// Header files
#include "nCurse.h"
#include <string>
#include <sstream>
#include "ClientConn.h"
using namespace std;
class Gui {
  
 public:

  Gui(ClientConn &);
  
  ~Gui();

  void paint(int, int, const string &);

  void fireAnimate(int, int, int, int);

  string input();

  //void write(const string&);

  string intToString(int&);
  int count;    
  
  nCurse * nC;
  bool alive;
  int offsetX, offsetY;

 private:

  // A pointer to an instance of Curse
  ClientConn * c;  

};
#endif
