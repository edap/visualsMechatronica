#pragma once
#include "ofMain.h"
#include "ofxAnimationPrimitives.h"
#include "ofxLayer.h"
#include "../layers/RotatingSpheres.h"

class Scene1 : public ofxAnimationPrimitives::Scene{
public:

    OFX_ANIMATION_PRIMITIVES_DEFINE_SCENE(Scene1);

    Scene1();
    void update();
    void draw();
    void viewWillAppear();
    void viewDidAppear();
    void viewWillDisappear();
    void viewDidDisappear();

    ofxLayer::Manager LM;
};
