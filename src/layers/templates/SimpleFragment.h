#pragma once
#include "../../Layer.h"
#include "ofxAutoReloadedShader.h"

using namespace ofxLayer;

class SimpleFragment : public ofxLayer::Layer {

public:
    void setup();
    void draw();
    virtual void loadAssets() = 0;
    virtual void setUniforms() = 0;

    ofxAutoReloadedShader shader;

private:
    bool checkGLVersion();
};
