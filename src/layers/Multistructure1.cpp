#include "Multistructure1.h"

void Multistructure1::loadAssets(){
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/multistructure1.frag", "");
    image.load("textures/budgeridgar/5a2.jpg");
}

void Multistructure1::setUniforms(){
    float resolution[] = { float(ofGetWidth()), float(ofGetHeight()) };
    float time = ofGetElapsedTimef();
    //int nBand = $Context(AudioAnalysis)->getBand();
    //float audioMag = $Context(Panel)->audioMag;
    //float smoothVal = $Context(Panel)->audioSmooth;
    float smoothVal = 1.6;
    float audioMag = 0.0075;
    int nBand = 1;
    float beat = $Context(AudioAnalysis)->getFilteredBand(nBand, smoothVal) * audioMag;
    float sdf2 = 0.7 - (max(0.0, beat * 0.3));

    shader.setUniform1f("iGlobalTime", time);
    shader.setUniform1f("beat", beat);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform1f("sdf2", sdf2);
    shader.setUniformTexture("tex0", image.getTexture(), 0);
}

float Multistructure1::max(float min, float max){
    return max > min ? max : min;
};
