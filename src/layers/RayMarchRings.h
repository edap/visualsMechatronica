#pragma once
#include "../Layer.h"
#include "ofxAutoReloadedShader.h"
#include "templates/SimpleFragment.h"

using namespace ofxLayer;

class RayMarchRings : public SimpleFragment {

public:
    OFX_LAYER_DEFINE_LAYER_CLASS(RayMarchRings)
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
    ofImage image7;
    ofImage image8;
    ofImage image9;
    ofImage image10;
};
