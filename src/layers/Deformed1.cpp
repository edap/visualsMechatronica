#include "Deformed1.h"

void Deformed1::loadAssets(){
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/blending_rings.frag", "");
    image0.load("textures/fischers-lovebird/fischers-lovebird-big.jpg");
}

void Deformed1::setUniforms(){
    float resolution[] = { float(ofGetWidth()), float(ofGetHeight()) };
    float time = ofGetElapsedTimef();

    //$Context(AppTime)->elapsed * 0.8;

    shader.setUniform1f("iGlobalTime",time);
    shader.setUniform2fv("resolution",resolution);
    shader.setUniformTexture("tex0",image0.getTexture(),0);
}

