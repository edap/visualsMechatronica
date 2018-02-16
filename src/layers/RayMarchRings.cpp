#include "RayMarchRings.h"

void RayMarchRings::setup(){
    ofDisableArbTex();
    plane.setResolution(2,2);
    plane.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    plane.set(ofGetWidth(), ofGetHeight());
    image0.load("textures/eastern-rosella-big.jpg");
    tex0 = image0.getTexture();

#ifdef TARGET_OPENGLES
    shader.load("shadersES2/shader");
#else
    if(ofIsGLProgrammableRenderer()){
        rayMarching.load("shaders_gl3/passthruogh.vert", "shaders_gl3/march1.frag", "");
    }else{
        rayMarching.load("shaders_gl3/passthruogh.vert", "shaders_gl3/march1.frag", "");
    }
#endif

}

void RayMarchRings::draw(){
    rayMarching.begin();
    setUniforms();
    plane.draw();
    rayMarching.end();
}

void RayMarchRings::setUniforms(){
    float resolution[] = {float(ofGetWidth()), float(ofGetHeight())};
    float time = ofGetElapsedTimef();
    rayMarching.setUniform1f("iGlobalTime",time);
    rayMarching.setUniform2fv("resolution",resolution);
    rayMarching.setUniformTexture("tex0",image0.getTexture(),0);
}
