#include "RayMarchRings.h"

void RayMarchRings::loadAssets(){
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/march1.frag", "");
    image0.load("textures/eastern-rosella-big.jpg");
}

void RayMarchRings::setUniforms(){
    float resolution[] = {float(ofGetWidth()), float(ofGetHeight())};
    float time = ofGetElapsedTimef();

    //$Context(AppTime)->elapsed * 0.8;

    shader.setUniform1f("iGlobalTime",time);
    shader.setUniform2fv("resolution",resolution);
    shader.setUniformTexture("tex0",image0.getTexture(),0);
}
