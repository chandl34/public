#include <stdlib.h>             /* for atoi */
#include <errno.h>              /* for ETIMEDOUT */
#include <signal.h>             /* for signal/SIGPIPE/SIG_IGN */
#include "ClientConn.h"
using namespace std;
ClientConn::ClientConn ( char *host, int portno ):
_host ( host ),
_port ( portno )
{
    signal ( SIGPIPE, SIG_IGN );    // Ignore SIGPIPEs 
}

bool
ClientConn::connect (  )
{
    sockerr lasterr ( 0 );
    try
    {
        _sio->connect ( _host, _port );
    }
    catch ( sockerr & e )
    {
        lasterr = e;
    }
    if ( lasterr.serrno (  ) != 0 )
    {
        cerr << "Connect failed, sockerr: " << lasterr.errstr (  ) << endl;
        return false;
    }
    _sio->recvtimeout ( 0 );    // Don't block on input
    _sio->sendtimeout ( 0 );    // Don't block on output

    return true;
}

string
ClientConn::receive (  )
{
    int rval;
    const int bufsize = 1024;
    char buf[bufsize];
    string rcvBuffer;
    try
    {
        rval = _sio->read ( buf, bufsize );
    }
    catch ( sockerr & e )
    {
        if ( e.serrno (  ) == ETIMEDOUT )
            return rcvBuffer;   // No input, done with this guy
        if ( e.serrno (  ) == ECONNRESET )
            rval = 0;           // He gone, flag to die him
        else
        {
            string s =
                "ConnectionError: Unspecified error during network read!";
            throw s.c_str (  );
        }
    }
    if ( rval == 0 )            // connection is closed
    {
        string s =
            "ConnectionResetError: Connection lost during network read!";
        throw s.c_str (  );
    }
    else if ( rval > 0 )        // Got new input
    {
        rcvBuffer += string ( buf, rval );  // stash input
    }
    return rcvBuffer;
}

void
ClientConn::send ( string _sendStr )
{
    _outputBuffer += _sendStr;
    int len = _outputBuffer.size (  );
    if ( len )
    {
        int wrote = 0;
        try
        {
            wrote = _sio->write ( _outputBuffer.c_str (  ), len );
            //Write all possible
        }
        catch ( const sockerr & e )
        {
            if ( e.serrno (  ) == ETIMEDOUT )
                return;
            if ( e.serrno (  ) == EPIPE )
                wrote = 0;      // And keep going
            else
            {
                string s = "ConnectionError: Network write error, ";
                throw s.c_str (  );
            }
        }
        catch ( int partial )
        {
            wrote = partial;
        }

        if ( wrote == len )
        {
            _outputBuffer.erase (  );   // Sent it all, flush
        }
        else if ( wrote > 0 )
        {                       // Partial write!
            _outputBuffer.erase ( 0, wrote );   // Strip off what we shipped
        }
        else                    //*** connection is closed!! 
        {
            string s = "ConnectionResetError: Connection lost during write!";
            throw s.c_str (  );
        }
    }
}
