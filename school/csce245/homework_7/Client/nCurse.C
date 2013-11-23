#include "nCurse.h"

nCurse* nCurse::Instance()
{
     static nCurse * ptr = NULL;
     if (!ptr) ptr = new nCurse;
     return ptr;
}

bool nCurse::Activate() {
    if (running) refresh();
    else {
        s = newterm((char *) 0,stdout,stdin);
        if (s != NULL) {
            set_term(s);
            width = COLS;
            height = LINES;
            curs_set(0); //uncomment it to get rid of the cursor
            noecho();
            cbreak();// Line buffering disabled. pass on everything
            nodelay(stdscr,1);
            keypad(stdscr, TRUE);
            running = true;
        }
    }
    return running;
}
nCurse::nCurse() {
    running = false;
}

void nCurse::Pause(size_t msecs)
{
    if (!running) return;
    struct timeval timeout;
    timeout.tv_sec = msecs/1000;
    timeout.tv_usec = (msecs%1000)*1000;
    select(0,0,0,0,&timeout);
}

unsigned short nCurse::GetCharAt(int x, int y)
{
      return (running ? mvinch(y,x) : 0);
}

int nCurse::ReadChar()
{
    if (!running) return -1;
    int ret = getch();
    if (ret==ERR) return -1;
    return ret;
}

void nCurse::Erase() {
    if (running) erase();
}

void nCurse::Redraw() {
    if (running) redrawwin(curscr);
}

void nCurse::PutCharAt(int x,int y,unsigned short ch){
     if (running) mvaddch(y,x,ch);
}

void nCurse::GoTo(int x,int y) {
    if (running) move(y,x);
}

void nCurse::Refresh() {
    if (running) refresh();
}

nCurse::~nCurse() {
    if (running) {
        noraw();
        echo();
        endwin();
        delscreen(s);
        keypad(stdscr, FALSE);
        running = false;
    }
}

