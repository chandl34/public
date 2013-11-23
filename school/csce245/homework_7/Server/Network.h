#ifndef NETWORK_H
#define NETWORK_H


#include <list>
#include <fstream>
#include <sstream>
#include <sockinet.h> 
using namespace std;
class ServerConn;               //forward declare

class Network {
public:


    ServerConn* s;
    Network(int portno = 0) ; // Initialize a network listener on a port

    ~Network() ;              // Clean up a network

    bool Accept() ;           // Check for new connections, accept one if so

    void receiveTempMsgs();   // Receive messages from temp users

    void receiveUserMsgs();   // Receive messages from users

    void admitNewUsers();

    void checkIfFinished();

    void addTemp(ServerConn *);

    void sendAll(string);

    int Count() const { return _us.size(); }             // User count
    int tempCount() const { return _tempNet.size(); }    // tempConn count

private:
    void Add(ServerConn *) ;  // Add a Connection to _us 

    void Remove(ServerConn *) ; // Remove a Connection from _us

    //ServerConn* admit(string, bool); 
    //when a conn gets a Helo msg, fn verifies, then adds to net


    void newConn(ServerConn*);  

    void newUser(ServerConn*);  

    void userRemoved(ServerConn*);  

    void tempRemoved(ServerConn*);  

    void mergeTemps();            
    //when destroying network, stick all temps on _us for delete


  string getNames();


//**** class misc functions ****
    string Host() const { return _si.localhost(); }      // Server host name
    int Port() const { return _si.localport(); }         // Server port
    void Fire(ServerConn *, int, int);
    bool canMove(int, int);

    sockinetbuf _si;		    // Sockbuf for listening for new connections
    typedef list<ServerConn*> Lcxn;   // Type for our user list
    Lcxn _us;                         // Master user list
    typedef list<ServerConn*> LtempCxn; 
    // Type for cxn list until admitted to game
    
    LtempCxn _tempNet;                  
    // list of accepted conns but not admitted to game

    friend class ServerConn;              
    //allow ServerConn access    

    bool gameRunning;
    
    int boundX, boundY;
   
    string map;
    
    int count;  
 
    string startingX[8];
    string startingY[8];  
    string intToString(int&);

};

#endif //Network.h



