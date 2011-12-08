#include <iostream>
#include <stdlib.h> /* for atoi() */
#include <unistd.h> /* for getlogin() */
#include <string>
#include "Gui.h"
#include "ClientConn.h"
using namespace std;

int main(int argc, char** argv) {

  char* hostname;
  int portno;
  string username;
  
  if (argc < 3 || argc > 4){
    cerr << "Usage: " << argv[0] << " HOSTNAME PORTNO [USERNAME] ..." << endl;
    return -1;
  }

  hostname = argv[1];
  portno = atoi(argv[2]);

  if (argc == 3)
    username = getlogin();  // be unix login name by default
  else                      // argc == 4
    username = argv[3];     // using what user provided

//  try {
  ClientConn c(hostname, portno);
  c.setName(username);
  Gui g(c);

  string clientMsg, serverMsg, tmp, tmp2, tmp3, tmp4;
  int serverMsgLength, clientMsgLength;
  int turn = 0;
  int msgNum;
  int boundX, boundY;
  int a, b;

  if (!c.connect()) {
	cerr << "Exiting, Attempt to connect failed!" << endl;
	return -1;
  }
  
  g.count++;
  tmp = g.intToString(g.count) + " HELO HUMAN WAR1.0 " + username;
  clientMsgLength = tmp.size();
  c.send(g.intToString(clientMsgLength) + ":" + tmp);  

//  }
//  catch {
//  }
  
  while(true) {
     /*********************** READ FROM KEYBOARD ***********************/
     g.nC->Pause(10);
     clientMsg = g.input();
     if (clientMsg!= "A") c.send(clientMsg);

     /*********************** LISTEN AND RESPOND ***********************/
     try{
        g.nC->Pause(10);
        serverMsg = c.receive();
     }
     catch (...){}   // DISCONNECT HERE LATER
     while(serverMsg != ""){     
         serverMsgLength = atoi(serverMsg.substr(0, serverMsg.find(":")).c_str());
         //cout << serverMsg.substr(0, serverMsgLength + serverMsg.find(":") + 1) << endl;
         //g.paint(0, 0, serverMsg.substr(0, serverMsgLength + serverMsg.find(":") + 1));
         serverMsg = serverMsg.substr(serverMsg.find(":") + 1);
         msgNum = atoi(serverMsg.substr(0, serverMsg.find(" ")).c_str());
         serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
         serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
         
         if(serverMsg.substr(0, serverMsg.find(" ")) == "HELO"){
             g.count++;
             tmp = g.intToString(g.count) + " MAPC";
             clientMsgLength = tmp.size();
             c.send(g.intToString(clientMsgLength) + ":" + tmp);
         }
         else if(serverMsg.substr(0, 6) == "BEGINS")
             g.alive = true;
         else if(serverMsg.substr(0, 4) == "MAPS"){
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
             boundX = atoi(serverMsg.substr(0, serverMsg.find(" ")).c_str());
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
             boundY = atoi(serverMsg.substr(0, serverMsg.find(" ")).c_str());
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
             tmp = serverMsg.substr(0, serverMsgLength);
             for(int p = 0; p < boundY; p++){
                 g.paint(g.offsetX, p + g.offsetY, tmp.substr(0, boundX));
                 tmp = tmp.substr(boundX);
             } 
             g.alive = true;
         }
         else if(serverMsg.substr(0, serverMsg.find(" ")) == "MOVE"){
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
             tmp = serverMsg.substr(0, serverMsg.find(" "));
             if(c.m.count(tmp) == 0){
                 c.m[tmp] = new Coord();
             }
             else
                 g.paint(c.m[tmp]->x + g.offsetX, c.m[tmp]->y + g.offsetY, " ");
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);        
             c.m[tmp]->x = atoi(serverMsg.substr(0, serverMsg.find(" ")).c_str());
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
             c.m[tmp]->y = atoi(serverMsg.substr(0, serverMsgLength).c_str());
             if(c.getName() == tmp)
                 g.paint(c.m[tmp]->x + g.offsetX, c.m[tmp]->y + g.offsetY, "O");
             else
                 g.paint(c.m[tmp]->x + g.offsetX, c.m[tmp]->y + g.offsetY, "X");
             g.nC->Refresh();
         }
         else if(serverMsg.substr(0, serverMsg.find(" ")) == "FIRE"){
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
             tmp = serverMsg.substr(0, serverMsg.find(" "));   // SHOOTER
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
             c.m[tmp]->x = atoi(serverMsg.substr(0, serverMsg.find(" ")).c_str());
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
             c.m[tmp]->y = atoi(serverMsg.substr(0, serverMsg.find(" ")).c_str());
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);     
             a = atoi(serverMsg.substr(0, serverMsg.find(" ")).c_str());
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
             b = atoi(serverMsg.substr(0, serverMsgLength).c_str());
             if(c.getName() == tmp)
                 g.paint(c.m[tmp]->x + g.offsetX, c.m[tmp]->y + g.offsetY, "O");
             else
                 g.paint(c.m[tmp]->x + g.offsetX, c.m[tmp]->y + g.offsetY, "X");
             g.nC->Refresh();
             g.fireAnimate(c.m[tmp]->x, c.m[tmp]->y, a, b);
         }
         else if(serverMsg.substr(0, serverMsg.find(" ")) == "KILL"){
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
             tmp = serverMsg.substr(0, serverMsg.find(" "));   // KILLER
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
             tmp2 = serverMsg.substr(0, serverMsg.find(" "));  // KILLED
             if(tmp2 == c.getName())
                 g.alive = false;
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
             c.m[tmp]->x = atoi(serverMsg.substr(0, serverMsg.find(" ")).c_str());
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
             c.m[tmp]->y = atoi(serverMsg.substr(0, serverMsg.find(" ")).c_str());
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);        
             c.m[tmp2]->x = atoi(serverMsg.substr(0, serverMsg.find(" ")).c_str());
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
             c.m[tmp2]->y = atoi(serverMsg.substr(0, serverMsgLength).c_str());
             if(c.getName() == tmp)
                 g.paint(c.m[tmp]->x + g.offsetX, c.m[tmp]->y + g.offsetY, "O");
             else
                 g.paint(c.m[tmp]->x + g.offsetX, c.m[tmp]->y + g.offsetY, "X");
             g.paint(c.m[tmp2]->x + g.offsetX, c.m[tmp2]->y + g.offsetY, " ");        
             g.nC->Refresh();
             g.fireAnimate(c.m[tmp]->x, c.m[tmp]->y, c.m[tmp2]->x, c.m[tmp2]->y);
         }
         else if(serverMsg.substr(0, serverMsg.find(" ")) == "WINNER"){
             serverMsgLength = serverMsgLength - serverMsg.find(" ") - 1;
             serverMsg = serverMsg.substr(serverMsg.find(" ") + 1);
             tmp = serverMsg.substr(0, serverMsgLength);
             g.alive = true;

             if(tmp == c.getName())
                 tmp = " YOU WIN! ";
             else
                 tmp = "GAME OVER!";
             tmp2 = ">>>>>";
             tmp3 = "     ";
             tmp4 = "<<<<<";
             g.paint(0, 22, tmp2);
             g.paint(75, 22, tmp4);
             g.nC->Refresh(); 
             g.nC->Pause(50);
             g.paint(5, 22, tmp2);
             g.paint(70, 22, tmp4);
             for(int o = 0; o < 14; o++){
                 if(o == 9)
                     g.paint(35, 22, tmp);
                 g.nC->Refresh();
                 g.nC->Pause(50);
                 g.paint(0 + o*5, 22, tmp3);
                 g.paint(10 + o*5, 22, tmp2);
                 g.paint(75 - o*5, 22, tmp3);
                 g.paint(65 - o*5, 22, tmp4);
             }
             g.nC->Refresh();
             g.nC->Pause(50);
             g.paint(70, 22, tmp3);
             g.paint(5, 22, tmp3);
             g.nC->Refresh();
             g.nC->Pause(50);
             g.paint(75, 22, tmp3);  
             g.paint(0, 22, tmp3);  
             g.nC->Refresh();
             g.nC->Pause(5000);
             g.paint(0, 22, "1: Start   2: Chat   3: Quit   arrow_keys: Move   number_pad: Shoot");
             g.nC->Refresh();
         }
         serverMsg = serverMsg.substr(serverMsgLength);
     }
  }
  return 0;
}

