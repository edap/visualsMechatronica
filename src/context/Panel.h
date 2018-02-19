#pragma once
#include "ofxGlobalContext.h"
#include "ofxGui.h"

class Panel : public ofxGlobalContext::Context{

public:
    Panel();
    void setup();
    void draw();

    ofxFloatSlider audioSmooth; // this value has always to be bigger than 0
    ofxFloatSlider audioMag;
    //ofxColorSlider dominant_color;
    ofxPanel gui;
};

