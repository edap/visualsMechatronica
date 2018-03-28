#include "Deformed1.h"

void Deformed1::loadAssets(){
    //shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/inside_rings.frag", "");
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/blob_stairs.frag", "");
    image0.load("textures/budgeridgar/5.jpg");
}

void Deformed1::setUniforms(){
    float resolution[] = { float(ofGetWidth()), float(ofGetHeight()) };
    float time = ofGetElapsedTimef();

    shader.setUniform2fv("resolution", resolution);

    shader.setUniform1f("iGlobalTime",time);
    shader.setUniform2fv("resolution",resolution);
    shader.setUniformTexture("tex0",image0.getTexture(),0);
}


