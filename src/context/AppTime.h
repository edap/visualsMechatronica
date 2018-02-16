#pragma once
#include "ofxGlobalContext.h"

class AppTime : public ofxGlobalContext::Context{
public:
    AppTime();
    void update();
    virtual ~AppTime() {}
    float tick;
    float elapsed;
    float rate;
};
