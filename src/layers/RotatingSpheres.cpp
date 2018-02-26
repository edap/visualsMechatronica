#include "RotatingSpheres.h"

void RotatingSpheres::loadAssets(){
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/two_spheres.frag", "");
    image0.load("textures/fischers-lovebird/fischers-lovebird3.jpg");
}

void RotatingSpheres::setUniforms(){
    float audioMag = 0.648;
    int nBand = 6;

    // debug with panel
    // $Context(AudioAnalysis)->setSmoothValue($Context(Panel)->audioSmooth);
    // float audioMag = $Context(Panel)->audioMag;
    // int nBand = $Context(AudioAnalysis)->getBand();
    float resolution[] = { float(ofGetWidth()), float(ofGetHeight()) };
    float time = ofGetElapsedTimef();

    float beat = $Context(AudioAnalysis)->getFilteredBand(nBand, 1.3) * audioMag;


    shader.setUniform1f("iGlobalTime", time);
    shader.setUniform1f("beat", beat);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniformTexture("tex0", image0.getTexture(), 0);
}

