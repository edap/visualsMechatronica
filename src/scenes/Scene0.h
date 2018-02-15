#pragma once
#include "ofMain.h"
#include "ofxAnimationPrimitives.h"
#include "ofxLayer.h"
#include "../layers/RayMarchRings.h"

class Scene0 : public ofxAnimationPrimitives::Scene{
public:

    OFX_ANIMATION_PRIMITIVES_DEFINE_SCENE(Scene0);

    Scene0(const int arg0);
    void update();
    void draw();
    void viewWillAppear();
    void viewDidAppear();
    void viewWillDisappear();
    void viewDidDisappear();

    ofxAnimationPrimitives::SceneManager SM;
    ofxLayer::Manager LM;
};
