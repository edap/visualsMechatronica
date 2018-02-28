#pragma once
#include "ofMain.h"
#include "ofxAnimationPrimitives.h"
#include "ofxLayer.h"
//#include "../layers/Blobby.h"
#include "../layers/Deformed2.h"

class Scene7 : public ofxAnimationPrimitives::Scene{
public:

    OFX_ANIMATION_PRIMITIVES_DEFINE_SCENE(Scene7);

    Scene7();
    void update();
    void draw();
    void viewWillAppear();
    void viewDidAppear();
    void viewWillDisappear();
    void viewDidDisappear();

    ofxLayer::Manager LM;
};
