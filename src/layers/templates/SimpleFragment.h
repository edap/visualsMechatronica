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

    // for fast prototyping, use ofxAutoReloadedShader
    // but keep in mind, you can not include libraries when using the auto reloader
    ofxAutoReloadedShader shader;

    // When the prototyping part is finished, and you are ready to ship, use ofShader and feel
    // free to include your libraries in your shader with
    // #pragma include "../libs/mercury.glsl", for example
    // ofShader shader;

private:
    bool checkGLVersion();
};
