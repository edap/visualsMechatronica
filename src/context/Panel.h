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

    // var utili per gli screenshot
    ofxFloatSlider u_camy;
    ofxFloatSlider u_camx;
    ofxFloatSlider u_fov;
    ofxIntSlider u_texId;

    //prototyping vars
    ofxFloatSlider time;
    ofxFloatSlider sdf1;
    ofxFloatSlider sdf2;
    ofxIntSlider sdfOp;
    ofxFloatSlider  sdfOpRadius;
    ofxFloatSlider sdfOpStairs;
    ofxIntSlider sdfSolidId1;
    ofxIntSlider sdfSolidId2;
    ofxIntSlider sdfModelId;
    ofxVec3Slider sdfSolid2Pos;
    ofParameter<ofColor> color;
};

