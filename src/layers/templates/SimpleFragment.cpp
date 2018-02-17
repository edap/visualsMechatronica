#include "SimpleFragment.h"

void SimpleFragment::setup(){
    ofDisableArbTex();
    if (checkGLVersion()) {
       loadAssets();
    }
}

void SimpleFragment::draw(){
    shader.begin();
    setUniforms();
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    shader.end();
}

bool SimpleFragment::checkGLVersion(){
    #ifdef TARGET_OPENGLES
        ofLogError("OPENGLES is not supported");
        return false;
    #else
        if (ofIsGLProgrammableRenderer()) {
            return true;
        } else {
            ofLogError("Only the Programmable Renderer pipeline is supported");
            return false;
        };
    #endif
}
