#include "MainFrame.h"
#include "InfoFrame.h"


int main (int argc, char * const argv[]) {
	Fl_Window mainWindow(MAIN_FRAME_SIZE[X] + INFO_FRAME_SIZE[X] + 30, 
								MAIN_FRAME_SIZE[Y] + 20 + MENU_HEIGHT, 
								"Tactics Map Editor");
	
	InfoFrame infoFrame(MAIN_FRAME_SIZE[X] + 20, 10 + MENU_HEIGHT, 
							  INFO_FRAME_SIZE[X], 
							  INFO_FRAME_SIZE[Y]);
	
	MainFrame mainFrame(10, 10 + MENU_HEIGHT, 
							  MAIN_FRAME_SIZE[X], 
							  MAIN_FRAME_SIZE[Y]);
	
	mainWindow.end();
	mainWindow.show();
	return Fl::run();
}