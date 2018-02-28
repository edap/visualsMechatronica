#include "Multistructure2.h"

void Multistructure2::loadAssets(){
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/multistructure2.frag", "");
    image.load("textures/eastern-rosella/eastern-rosella-det.jpg");
}

void Multistructure2::setUniforms(){
    float resolution[] = { float(ofGetWidth()), float(ofGetHeight()) };
    float time = ofGetElapsedTimef();
    //int nBand = $Context(AudioAnalysis)->getBand();
    //float audioMag = $Context(Panel)->audioMag;
    //float smoothVal = $Context(Panel)->audioSmooth;
    float smoothVal = 2.632;
    float audioMag = 0.001;
    int nBand = 1;
    float beat = $Context(AudioAnalysis)->getFilteredBand(nBand, smoothVal) * audioMag;
    float sdf2 = 0.85 - max(0., beat);
    shader.setUniform1f("iGlobalTime", time);
    shader.setUniform1f("beat", beat);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform1f("sdf2", sdf2);
    shader.setUniformTexture("tex0", image.getTexture(), 0);
}

float Multistructure2::max(float min, float max){
    return max > min ? max : min;
};
