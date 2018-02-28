#pragma once
#include "../Layer.h"
#include "ofxAutoReloadedShader.h"
#include "templates/SimpleFragment.h"
#include "../context/AudioAnalysis.h"
#include "../context/Panel.h"

using namespace ofxLayer;

class Multistructure3 : public SimpleFragment {

public:
    OFX_LAYER_DEFINE_LAYER_CLASS(Multistructure3)
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

    float max(float min, float max);
};
