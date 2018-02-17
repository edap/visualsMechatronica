#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 2);
    settings.width = 1080;
    settings.height = 1080;
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}
