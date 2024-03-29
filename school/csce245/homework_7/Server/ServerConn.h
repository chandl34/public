#ifndef SERVERCONN_H
#define SERVERCONN_H

#include <list>
#include <sockinet.h> 
using namespace std;
class Network;       // Forward

class ServerConn {
public:

    ServerConn(Network & n, iosockinet *i,sockinetaddr p) ;

    virtual ~ServerConn() ;	   // Unlink from Network's connection list

    void send(string) ;            // Try to write on this connection

    void killConn();               //kills this connection

    void setName(string name){_userName = name;}

    string getName(){return _userName;}

    string receive() ;             // Try to read on this connection

    int x, y;
    int turn;   

private:
    const string Host() const { return _peer.gethostname(); } // Far end name
    const int Port() const { return _peer.getport(); }      // and port #
    void Finalize() ;                                       
    // Give one last chance before closing

    string _userName;              //at login, name of user from Helo msg
    string _outputBuffer;	   // Stuff pending to send to guy
    Network & _net;		   // The network conn accepted from
    sockinetaddr _peer;		   // Where this connection originated
    iosockinet * _s;		   // A guy we're connected to

  friend class Network;

  ServerConn(ServerConn &) ;               // Declare away
  void operator=(ServerConn&) ;            // Declare away

  bool readyToPlay, alive;
};

#endif /* ServerConn.h */


