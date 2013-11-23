#include "gl/Game_Window.h"
#include "ui/UI_Window.h"

int main(int argc, char** argv){
	int totalWidth = 1024;
	int totalHeight = 768;
	int uiHeight = (int)(totalHeight*0.233f);
	int gameHeight = totalHeight - uiHeight;
	
    Fl_Window mainWindow(totalWidth, totalHeight, "I AM BATMAN");
    Game_Window gameWin(0, 0, totalWidth, gameHeight);
    UI_Window uiWin(0, gameHeight, totalWidth, uiHeight);
    
    mainWindow.show();
    mainWindow.cursor(FL_CURSOR_NONE);
    return(Fl::run());
}
