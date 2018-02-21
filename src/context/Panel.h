#pragma once
#include "ofxGlobalContext.h"
#include "ofxGui.h"

class Panel : public ofxGlobalContext::Context{

public:
    Panel();
    void setup();
    void draw();

    ofxPanel gui;

    ofxFloatSlider audioSmooth; // this value has always to be bigger than 0
    ofxFloatSlider audioMag;

    //prototyping vals
    ofxFloatSlider sdf1;
    ofxFloatSlider sdf2;
    ofxIntSlider sdfOp;
    ofxIntSlider sdfSolidId1;
    ofxIntSlider sdfSolidId2;
    ofxVec3Slider sdfSolid2Pos;
};

