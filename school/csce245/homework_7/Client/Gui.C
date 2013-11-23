#include "Gui.h"
#include "nCurse.h"
#include <string>
#include <sstream>
#include <vector>

Gui::Gui(ClientConn & c1){

  c = &c1;
  alive = false;

  // Create an instance of Curse
  nC = nCurse::Instance();

  nC->Activate();  

  nC->Refresh();
  count = 0;
  offsetX = 5;
  offsetY = 4;

  // Map is 70x14
  string top(80, '#');
  string tmp = "#####";
  string tmp2(70, ' ');
  string side = tmp + tmp2 + tmp;
  // Instruction menu
  string instructions = "1: Start   2: Chat   3: Quit   arrow_keys: Move   number_pad: Shoot";  

  for(int i = 0; i < 4; i++)
      paint(0, i, top);      
  for(int i = 4; i < 18; i++)
      paint(0, i, side); 
  for(int i = 18; i < 22; i++)
      paint(0, i, top); 
  paint(0, 22, instructions);
}

// Destructor. 
Gui::~Gui() { 

  // Get the garbage off the screen
  nC->GoTo(0,0);
  nC->Erase();
  nC->Refresh();
  
  // Terminate the instance of Curse
  delete nC; 
}

// Paint function - an auxiliary which makes life easier
void Gui::paint(int x,int y, const string & p){
  for (size_t i = 0; i < p.size(); i++) nC->PutCharAt(x+i,y,p[i]);
}

// Outputs strings for the message factory
string Gui::input(){ 
  int command;
  int msgLength;
  string tmp;
  char msg[5];
  msg[1] = '\0';
  nC->Refresh();

  // Get the input from the user
  command = nC->ReadChar();
  // If no command was issued, or if an invalid key
  // was hit, just return nothing         
  if(alive){          
      if (command == KEY_LEFT) {
          count++;
          tmp =  intToString(count) + " MOVE " + c->getName() + " -1 0";
          msgLength = tmp.size();
          tmp = intToString(msgLength) + ":" + tmp;
          return tmp;
      }
      else if (command == KEY_RIGHT) {
          count++;
          tmp =  intToString(count) + " MOVE " + c->getName() + " 1 0";
          msgLength = tmp.size();
          tmp = intToString(msgLength) + ":" + tmp;
          return tmp;
      }
      else if (command == KEY_UP) {
          count++;
          tmp =  intToString(count) + " MOVE " + c->getName() + " 0 -1";
          msgLength = tmp.size();
          tmp = intToString(msgLength) + ":" + tmp;
          return tmp;
      }
      else if (command == KEY_DOWN) {
          count++;
          tmp =  intToString(count) + " MOVE " + c->getName() + " 0 1";
          msgLength = tmp.size();
          tmp = intToString(msgLength) + ":" + tmp;
          return tmp;
      }
      else if(command == '1'){
          count++;
          tmp = intToString(count) + " BEGINC";
          msgLength = tmp.size();
          tmp = intToString(msgLength) + ":" + tmp;
          return tmp;
      }
      else if(command == 'w'){  // SHOOT TOP LEFT
          count++;
          tmp = intToString(count) + " FIRE " + c->getName() + " -1 -1";
          msgLength = tmp.size();
          tmp = intToString(msgLength) + ":" + tmp;
          return tmp;
      }
      else if(command == 'x'){  // SHOOT TOP
          count++;
          tmp = intToString(count) + " FIRE " + c->getName() + " 0 -1";
          msgLength = tmp.size();
          tmp = intToString(msgLength) + ":" + tmp;
          return tmp;
      }
      else if(command == 'y'){  // SHOOT TOP RIGHT
          count++;
          tmp = intToString(count) + " FIRE " + c->getName() + " 1 -1";
          msgLength = tmp.size();
          tmp = intToString(msgLength) + ":" + tmp;
          return tmp;
      }
      else if(command == 'v'){  // SHOOT RIGHT
          count++;
          tmp = intToString(count) + " FIRE " + c->getName() + " 1 0";
          msgLength = tmp.size();
          tmp = intToString(msgLength) + ":" + tmp;
          return tmp;
      }
      else if(command == 's'){  // SHOOT BOTTOM RIGHT
          count++;
          tmp = intToString(count) + " FIRE " + c->getName() + " 1 1";
          msgLength = tmp.size();
          tmp = intToString(msgLength) + ":" + tmp;
          return tmp;
      }
      else if(command == 'r'){  // SHOOT BOTTOM
          count++;
          tmp = intToString(count) + " FIRE " + c->getName() + " 0 1";
          msgLength = tmp.size();
          tmp = intToString(msgLength) + ":" + tmp;
          return tmp;
      }
      else if(command == 'q'){  // SHOOT BOTTOM LEFT
          count++;
          tmp = intToString(count) + " FIRE " + c->getName() + " -1 1";
          msgLength = tmp.size();
          tmp = intToString(msgLength) + ":" + tmp;
          return tmp;
      }
      else if(command == 't'){  // SHOOT LEFT
          count++;
          tmp = intToString(count) + " FIRE " + c->getName() + " -1 0";
          msgLength = tmp.size();
          tmp = intToString(msgLength) + ":" + tmp;
          return tmp;
      }
      else {
          //msg[0] = command;
          return "A";
      }
  }
  else
      return "A";
}

string Gui::intToString(int & num){
    stringstream ss;
    string str;
    ss << num;
    ss >> str; 
    return str;
}

void Gui::fireAnimate(int x1, int y1, int x2, int y2){ 
   int xd, yd;
   int tmpX = x1;
   int tmpY = y1;
   if(x1 > x2)
       xd = -1;
   else if(x1 == x2)
       xd = 0;
   else
       xd = 1;
   if(y1 > y2)
       yd = -1;
   else if(y1 == y2)
       yd = 0;
   else
       yd = 1;
   string tmp;
   if(xd == 0)
       tmp = "|";
   else if(yd == 0)
       tmp = "-";
   else if(xd != yd)
       tmp = "/";
   else
       tmp = "\\";
   x1 += xd;
   y1 += yd;
   while(x1 != x2 || y1 != y2){ 
       paint(x1 + offsetX, y1 + offsetY, tmp);
       x1 += xd;
       y1 += yd;
   }
   nC->Refresh();
   nC->Pause(30);
   x1 = tmpX;
   y1 = tmpY;
   x1 += xd;
   y1 += yd;
   while(x1 != x2 || y1 != y2){       
       paint(x1 + offsetX, y1 + offsetY, " ");
       x1 += xd;
       y1 += yd;
   }
   nC->Refresh();
}
