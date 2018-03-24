#include "Deformed2.h"

void Deformed2::loadAssets(){
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/bend_five_rings.frag", "");
    image0.load("textures/eastern-rosella/eastern-rosella.jpg");
}

void Deformed2::setUniforms(){
    float resolution[] = { float(ofGetWidth()), float(ofGetHeight()) };
    float time = ofGetElapsedTimef();

    //$Context(AppTime)->elapsed * 0.8;

    shader.setUniform1f("iGlobalTime",time);
    shader.setUniform2fv("resolution",resolution);
    shader.setUniformTexture("tex0",image0.getTexture(),0);
}


