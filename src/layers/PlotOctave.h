#pragma once
#include "../Layer.h"
#include "../context/AudioAnalysis.h"

using namespace ofxLayer;

class PlotOctave : public ofxLayer::Layer {

public:
    OFX_LAYER_DEFINE_LAYER_CLASS(PlotOctave)

    void draw();
};
