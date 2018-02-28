#pragma once
#include "../Layer.h"
#include "ofxAutoReloadedShader.h"
#include "templates/SimpleFragment.h"
#include "../context/AudioAnalysis.h"
#include "../context/Panel.h"

using namespace ofxLayer;

class Multistructure2 : public SimpleFragment {

public:
    OFX_LAYER_DEFINE_LAYER_CLASS(Multistructure2)
    void setUniforms();
    void loadAssets();

private:
    ofImage image;

    float max(float min, float max);
};
