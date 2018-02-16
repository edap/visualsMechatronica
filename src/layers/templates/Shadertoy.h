#pragma once
#include "../../Layer.h"
#include "ofxAutoReloadedShader.h"

using namespace ofxLayer;

class Shadertoy : public ofxLayer::Layer {

public:

    void setup();
    void draw();

private:
    void setUniforms();

    ofxAutoReloadedShader shader;
    ofImage               image0;
    ofTexture             tex0;
    ofPlanePrimitive      plane;
};
