#include "Multistructure3.h"

void Multistructure3::loadAssets(){
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/Multistructure3.frag", "");
    image4.load("textures/fischers-lovebird/fischers-lovebird3.jpg");
}

void Multistructure3::setUniforms(){
    float resolution[] = { float(ofGetWidth()), float(ofGetHeight()) };
    float time = ofGetElapsedTimef();
    //int nBand = $Context(AudioAnalysis)->getBand();
    //float audioMag = $Context(Panel)->audioMag;
    // $Context(AudioAnalysis)->setSmoothValue($Context(Panel)->audioSmooth);
    // float smoothVal = $Context(Panel)->audioSmooth;
    float smoothVal = 1.12;
    float audioMag = 0.024;
    int nBand = 1;
    float beat = $Context(AudioAnalysis)->getFilteredBand(nBand, smoothVal) * audioMag;

    float sdf2 = 0.335 * (0.1 + max(0.0, beat));

    shader.setUniform1f("iGlobalTime", time);
    shader.setUniform1f("beat", beat);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform1f("sdf2", sdf2);

    shader.setUniformTexture("tex4", image4.getTexture(), 4);

}

float Multistructure3::max(float min, float max){
    return max > min ? max : min;
};