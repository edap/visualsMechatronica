#pragma once
#include "../Layer.h"
#include "ofxAutoReloadedShader.h"
#include "templates/SimpleFragment.h"
#include "../context/AudioAnalysis.h"
#include "../context/Panel.h"

using namespace ofxLayer;

class RotatingSpheres : public SimpleFragment {

public:
    OFX_LAYER_DEFINE_LAYER_CLASS(RotatingSpheres)
    void setUniforms();
    void loadAssets();

private:
    void setOctaves();
    ofImage image0;
};
