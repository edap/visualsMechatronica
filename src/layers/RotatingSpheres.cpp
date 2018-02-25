#include "RotatingSpheres.h"

void RotatingSpheres::loadAssets(){
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/two_spheres.frag", "");
    image0.load("textures/fischers-lovebird/fischers-lovebird3.jpg");
}

void RotatingSpheres::setUniforms(){
    float resolution[] = { float(ofGetWidth()), float(ofGetHeight()) };
    float time = ofGetElapsedTimef();
    int n_band = $Context(AudioAnalysis)->getBand();
    float beat = $Context(AudioAnalysis)->getFilteredBand(6) * 0.648;

    //float b = $Context(AudioAnalysis)->smoothBand(6) * $Context(Panel)->audioMag;
    //cout << b << endl;

    shader.setUniform1f("iGlobalTime", time);
    shader.setUniform1f("beat", beat);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniformTexture("tex0", image0.getTexture(), 0);
}

