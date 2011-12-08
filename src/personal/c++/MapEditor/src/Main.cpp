#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include "gl/Map_Window.h"
#include "preview/Preview_Window.h"
#include "preview/Model_Window.h"
#include "Include.h"

int main(int argc, char** argv){    
    Preview_Window previewWindow(280, 300, "Model Selection");
    
    Model_Window* groundWin = new Model_Window(GROUND, 10, 30, 80, 80);
    Model_Window* debrisWin = new Model_Window(DEBRIS, 100, 30, 80, 80);
    Model_Window* grassWin = new Model_Window(GRASS, 190, 30, 80, 80);
    Model_Window* wallWin = new Model_Window(WALL, 10, 120, 80, 80);
    Model_Window* objectWin = new Model_Window(OBJECT, 100, 120, 80, 80);
    Model_Window* fenceWin = new Model_Window(FENCE, 190, 120, 80, 80);
    Model_Window* windowFrameWin = new Model_Window(WINDOWFRAME, 10, 210, 80, 80);
    Model_Window* doorWin = new Model_Window(DOOR, 100, 210, 80, 80);
    Model_Window* doorFrameWin = new Model_Window(DOORFRAME, 190, 210, 80, 80);
    
    previewWindow.addWindow(groundWin);
    previewWindow.addWindow(debrisWin);
    previewWindow.addWindow(grassWin);
    previewWindow.addWindow(wallWin);
    previewWindow.addWindow(objectWin);
    previewWindow.addWindow(fenceWin);
    previewWindow.addWindow(windowFrameWin);
    previewWindow.addWindow(doorWin);
    previewWindow.addWindow(doorFrameWin);

    Fl_Window mainWindow(WIDTH, HEIGHT, "Map Editor");
    Map_Window mapWin(10, 10, WIDTH-20, HEIGHT-20);
    
    mainWindow.show();
    previewWindow.show();
    return(Fl::run());
}
