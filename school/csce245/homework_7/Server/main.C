#include <sockinet.h>
#include <iostream>
#include "Network.h"
#include "ServerConn.h"
#include <Errors.h>
#include <string>
using namespace std;
#define PORTNUM 2010
int main (int argc, char** argv)
{
    int port = PORTNUM;
    if (argc==2) port = atoi(argv[1]);
    if (port<2000 || port>30000) {
	 cerr << "Usage: " << argv[0] << " [portnumber: 2000..30000]" << endl;
        return 1;
    }
    Network* n = new Network(port);
    string tmp;
    bool readyToStop = false;

    do{  
	 if(n->Accept()){
            n->addTemp(n->s);
	     readyToStop = true;
	 }
        n->receiveTempMsgs();
	 n->receiveUserMsgs();
        n->checkIfFinished();
        n->admitNewUsers();       
    }while(!readyToStop || n->Count() != 0 || n->tempCount() != 0);
    
    /*************************************************************************	
    while(true) {
        if (n->Accept() == true) {
            cout << "Got connection\n";
            break;
        }
    }
    while(true){
        try{
            tmp = n->s->receive();
        }
        catch (ConnectionResetError & e){ //connection lost
            break;
        }
       if (tmp != "") cout << tmp << endl;
    }
    *************************************************************************/
//    delete n->s; //no need, because when lost connection, it has been killed
//                 // by KillConn.
    delete n;
    return 0;
    
}
