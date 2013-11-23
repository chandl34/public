#ifndef PREVIEW_WINDOW_H_
#define PREVIEW_WINDOW_H_

#include <boost/serialization/vector.hpp>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_File_Chooser.H>
#include "Model_Window.h"
#include "../gl/Map_Window.h"
#include "../io/Data.h"

class Preview_Window : public Fl_Window{
public:
	Preview_Window(int, int, char*);
	virtual ~Preview_Window();
	
	void addWindow(Model_Window* mw){mWin.push_back(mw);}
	
	static void toggleMirror();
	static void toggleInvert();
	static void toggleShift();
	static void setRotate(int);
	static void toggleCondition(int);
	
private:
	static void File_CB(Fl_Widget*, void*);
	static void Toggle_CB(Fl_Widget*, void*);
	static void findRelativePath();
	
	static MapModelContainer* mapModels;
	static string relativePath;	
	static string mapFolder, objFolder;
	static Fl_Menu_Bar* menubar;
	static Fl_File_Chooser* fileChooser;
	static vector<Model_Window*> mWin;	
};

#endif /*PREVIEW_WINDOW_H_*/
