#ifndef DECODE_H_
#define DECODE_H_

#include <string>
using namespace std;
class Decode
{

public:
	Decode():count(0),num(0),state(WHITE){}
    
	~Decode(){}
    
	string Read(string input);
    bool remain() {
        if (preBuffer.size() > 0) return true;
        else return false;
    }

private:
    
	string preBuffer;
    string buffer;
    int count;
    int num;
    enum {WHITE,DIGIT,COUNT} state;
};

#endif
