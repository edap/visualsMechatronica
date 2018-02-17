#pragma once
#include "../Layer.h"
#include "ofxAutoReloadedShader.h"
#include "templates/SimpleFragment.h"

using namespace ofxLayer;

class Multistructure : public SimpleFragment {

public:
    OFX_LAYER_DEFINE_LAYER_CLASS(Multistructure)
    void setUniforms();
    void loadAssets();

private:
    ofImage image0;
};
