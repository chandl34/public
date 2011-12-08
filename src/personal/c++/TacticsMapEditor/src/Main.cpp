#include "Include.h"
#include "gl/MapWindow.h"

int main(){
	MapWindow mapWin(0, 0, 800, 600);
	mapWin.show();
    return(Fl::run());
}
