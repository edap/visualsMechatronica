#pragma once
#include "ofxGlobalContext.h"
#include "ofxGui.h"

// From 'Live', by by Yuma Taesu

class AppTime : public ofxGlobalContext::Context{
public:

    float tick;
    float elapsed;
    float rate;

    AppTime(){
        elapsed = 0;
        rate = 0;
    }

    void update(){
        float inv_target_frame = (1. / 60);
        tick = ofGetLastFrameTime();
        rate = tick / inv_target_frame;
        elapsed += tick;
    }
};

void init_context(){
    ofxGlobalContext::Manager::defaultManager().createContext<AppTime>();
}
