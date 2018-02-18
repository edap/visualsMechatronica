#include "ofxGlobalContext.h"
#include "ofxGui.h"

class Panel : public ofxGlobalContext::Context{

public:
    Panel();
    void setup();
    void draw();

    ofxFloatSlider displacement;
    //ofxColorSlider dominant_color;
    ofxPanel gui;
};

