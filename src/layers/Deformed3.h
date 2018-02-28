#pragma once
#include "../Layer.h"
#include "ofxAutoReloadedShader.h"
#include "templates/SimpleFragment.h"

using namespace ofxLayer;

class Deformed3 : public SimpleFragment {

public:
    OFX_LAYER_DEFINE_LAYER_CLASS(Deformed3)
    void setUniforms();
    void loadAssets();

private:
    ofImage image0;
};
