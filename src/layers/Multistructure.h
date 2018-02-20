#pragma once
#include "../Layer.h"
#include "ofxAutoReloadedShader.h"
#include "templates/SimpleFragment.h"
#include "../context/AudioAnalysis.h"
#include "../context/Panel.h"

using namespace ofxLayer;

class Multistructure : public SimpleFragment {

public:
    OFX_LAYER_DEFINE_LAYER_CLASS(Multistructure)
    void setUniforms();
    void loadAssets();

private:
    ofImage image0;
    ofImage image1;
    ofImage image2;
    ofImage image3;
    ofImage image4;
    ofImage image5;
    ofImage image6;
};
