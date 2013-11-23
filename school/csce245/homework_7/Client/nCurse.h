#ifndef N_CURSE_H_
#define N_CURSE_H_

#include <ncurses.h>
#include <iostream>
using namespace std;

class nCurse {
        nCurse();
        bool running;
        int height;
        int width;
        SCREEN* s;
    public: 
        ~nCurse();
        bool Activate();
        static nCurse* Instance();
        int ReadChar();
        void Redraw();
        void Erase();
        void PutCharAt(int x,int y,unsigned short ch);
        short unsigned int GetCharAt(int, int);
        void GoTo(int x,int y);
        void Refresh();
        void Pause(size_t msecs);
};
#endif
