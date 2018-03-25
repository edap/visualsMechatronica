#include "Deformed3.h"

void Deformed3::loadAssets(){
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/multimaterial.frag", "");
    image0.load("textures/eastern-rosella/eastern-rosella.jpg");
    image1.load("textures/fischers-lovebird/fischers-lovebird3.jpg");
    image2.load("textures/budgeridgar/5.jpg");
}

void Deformed3::setUniforms(){
    float resolution[] = { float(ofGetWidth()), float(ofGetHeight()) };
    float time = ofGetElapsedTimef();

    //$Context(AppTime)->elapsed * 0.8;

    shader.setUniform1f("iGlobalTime",time);
    shader.setUniform2fv("resolution",resolution);
    shader.setUniformTexture("tex0",image0.getTexture(),0);
    shader.setUniformTexture("tex1",image1.getTexture(),1);
    shader.setUniformTexture("tex2",image2.getTexture(),2);
}


