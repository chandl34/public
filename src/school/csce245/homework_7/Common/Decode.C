#include <string>
#include <ctype.h>
#include "Errors.h"
#include "Decode.h"

string Decode::Read(string input)
{
	preBuffer+=input;
	string s;
	size_t i;
    char c;
	for(i=0;i<preBuffer.size();++i)
	{
        c = preBuffer[i];
	    switch(state)  //what state are we in
        {
            case WHITE: //reading whitespace
                if (isspace(c) ) break; //keep reading
    		    if( isdigit(c) ) //digit, switch states
		        {
			        buffer+=c;
			        state=DIGIT;
    		    }
	    		else //non-white, non-digit
		    	{
                    string s="Parse Error: Bad input, expected digit";
					throw ParsingError(s.c_str());
                }
                break;
           case DIGIT:
               if(isdigit(c)) //keep adding to buffer
			   {
                   buffer+=c;
                   break;
               }
               if(c==':') //end of buffer size
               {
                    state=COUNT; //change to count state
                    count=atoi( buffer.c_str() ); //build _count
                    buffer.erase();//empty the internal buffer
               }
               else //found a non-digit, non-colon
               {
					string s="Parse Error: Bad input, expected digit or colon";
					throw ParsingError(s.c_str());

               }

               break;
           case COUNT://reading count number of bytes
               buffer+=c;
               count--;
               if(count==0) //done reading, return the string
               {
                   state=WHITE;//reset the state
                   s=buffer;
                   buffer.erase();
               }
               break;
        }
        if(s.size()>0) break;
    }
    preBuffer.erase(0,i+1);
    return s;
}
