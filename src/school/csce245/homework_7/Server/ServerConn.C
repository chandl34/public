#include "ServerConn.h"
#include "Network.h"
#include <Errors.h>
#include <iostream>
#include <errno.h>     /* for ETIMEDOUT */
#include <algorithm>   /* for find() */


ServerConn::ServerConn(Network & n, iosockinet *i,sockinetaddr p) 
  : _net(n), _peer(p), _s(i)
{
    (*_s)->recvtimeout(0);              // Don't block on input from this guy
    (*_s)->sendtimeout(0);              // Don't block on output to this guy
    readyToPlay = false;
    turn = 0;
    alive = false;
}

ServerConn::~ServerConn() 	        // Lost a user
{
//	_net.Remove(this);              //remove
    delete _s;                          // toss the iosockinet
}

void ServerConn::killConn()
{
    //ContactClosed();                  //notify of death
    delete this;                        //rmv from network also
}

string ServerConn::receive() 
{
    int rval;
    const int bufsize=1024;
    char buf[bufsize];		                  // Get a buffer
    string receiveBuffer;
    try {rval = (*_s)->read(buf,bufsize);}       // Try the read
    catch (const sockerr & e) {
       if (e.serrno() != ETIMEDOUT)      //caught sockerr, NOT a timeout
       {
           string s = "ConnectionError: During network read, Unspecified error";
           throw ConnectionError(s.c_str());
        }
        return receiveBuffer;
    }
    if (rval==0) {               // Return of 0 means connection closed
	killConn();
	string s = "ConnectionResetError: Connection lost during network read!";
    throw ConnectionResetError(s.c_str());
    } 
    if (rval>0) 
	receiveBuffer += (string(buf, rval));     //add to buffer

    return receiveBuffer;

}

void ServerConn::send(string _sendStr)
{
    _outputBuffer += _sendStr;
    int len = _outputBuffer.size();	          // Check output buffer size

    if (len)                                      // Have something to send
    {
        int wrote = 0;
        try {
            wrote = (*_s)->write(_outputBuffer.data(),len); 
            // Write all possible
        }
        catch (const sockerr & e)
        {
            if (e.serrno()==ETIMEDOUT) return;
            if (e.serrno()==EPIPE) wrote = 0;   //keep going
            else {
                killConn();
                string s = "ConnectionError: Unspecified network write error, ";
                throw ConnectionError(s.c_str());
            }
        }
        catch (int partial) {
            wrote = partial;                      // keep going
        }
        if (wrote==len) {
            _outputBuffer.erase();		  // Sent it all, flush
        } 
        else 
	    if (wrote>0)                          // Partial write!
	    {	
            _outputBuffer.erase(0,wrote);     // Strip off what we shipped
	    } 
	    else // got an EPIPE or partial was negative?? 
	    {
            killConn();
            string s = "ConnectionResetError: Connection lost during network write!";
            throw ConnectionResetError(s.c_str());
	    }
    }
}


