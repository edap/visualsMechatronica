#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 2);
    settings.setSize(1920, 1024);
    //settings.windowMode = OF_GAME_MODE;
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}
