#pragma once
#include "ofMain.h"
#include "ofxAnimationPrimitives.h"
#include "ofxLayer.h"
//#include "../layers/Blobby.h"
#include "../layers/Cup.h"

class Scene5 : public ofxAnimationPrimitives::Scene{
public:

    OFX_ANIMATION_PRIMITIVES_DEFINE_SCENE(Scene5);

    Scene5();
    void update();
    void draw();
    void viewWillAppear();
    void viewDidAppear();
    void viewWillDisappear();
    void viewDidDisappear();

    ofxLayer::Manager LM;
};
