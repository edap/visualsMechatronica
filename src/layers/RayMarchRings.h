#pragma once
#include "../Layer.h"
#include "ofxAutoReloadedShader.h"

using namespace ofxLayer;

class RayMarchRings : public ofxLayer::Layer {

public:
    OFX_LAYER_DEFINE_LAYER_CLASS(RayMarchRings)

    void setup();
    void draw();

private:
    void setUniforms();

    ofxAutoReloadedShader rayMarching;
    ofImage               image0;
    ofTexture             tex0;
    ofPlanePrimitive      plane;
};
