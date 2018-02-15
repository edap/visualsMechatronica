#pragma once
#include "ofxLayer.h"

class Layer : public ofxLayer::Layer
{
public:
    virtual void reload() {}
    virtual void bang() {}
};
