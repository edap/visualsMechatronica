#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 2);
    //settings.setSize(1280,720);
    //settings.setSize(1920,1080);
    //settings.windowMode = OF_FULLSCREEN;
    //settings.setSize(2560,1480);
    settings.setSize(3840,2160);
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}
