#ifndef CLIENTCONN_H
#define CLIENTCONN_H

#include <sockinet.h>
#include "Coord.h"
#include <string>
#include <map>
using namespace std;
class ClientConn
{
 public:

    ClientConn(char * host, int portno);     //ctor needs a host addr and port#


    bool connect();        //actually makes the connection, rtns true if ok


    string receive();     //gets stuff from net and returns a string

    void send(string _sendStr);    //takes a str, buffers it, sends till done

    void setName(string name){_userName = name;}

    string getName(){return _userName;}

    map<string, Coord*> m;

 private:
    ClientConn(ClientConn &) ;               // Declare away
    void operator=(ClientConn&) ;            // Declare away
    string _userName;
    char * _host;  
    int _port;
    iosockinet _sio;
    string _outputBuffer;
};

#endif



