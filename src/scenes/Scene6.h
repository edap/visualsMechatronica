#pragma once
#include "ofMain.h"
#include "ofxAnimationPrimitives.h"
#include "ofxLayer.h"
//#include "../layers/Blobby.h"
#include "../layers/Multistructure.h"

class Scene6 : public ofxAnimationPrimitives::Scene{
public:

    OFX_ANIMATION_PRIMITIVES_DEFINE_SCENE(Scene6);

    Scene6();
    void update();
    void draw();
    void viewWillAppear();
    void viewDidAppear();
    void viewWillDisappear();
    void viewDidDisappear();

    ofxLayer::Manager LM;
};
