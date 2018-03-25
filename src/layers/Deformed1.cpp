#include "Deformed1.h"

void Deformed1::loadAssets(){
    //shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/inside_rings.frag", "");
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/blob_stairs.frag", "");
    image0.load("textures/budgeridgar/5.jpg");
}

void Deformed1::setUniforms(){
    float resolution[] = { float(ofGetWidth()), float(ofGetHeight()) };
    float time = ofGetElapsedTimef();

    int nBand = $Context(AudioAnalysis)->getBand();
    float audioMag = $Context(Panel)->audioMag;
    float smoothVal = $Context(Panel)->audioSmooth;

    //float smoothVal = 0.902;
    //float audioMag = 0.0175;
    //int nBand = 1;
    float beat = $Context(AudioAnalysis)->getFilteredBand(nBand, smoothVal) * audioMag;
    float beatB = $Context(AudioAnalysis)->getFilteredBand(nBand, smoothVal) * audioMag;

//    cout << beat << endl;
//    cout << "-" << endl;
//    cout << beatB << endl;

    shader.setUniform1f("beat", beat);
    shader.setUniform1f("beat2", beatB);
    shader.setUniform2fv("resolution", resolution);

    shader.setUniform1f("iGlobalTime",time);
    shader.setUniform2fv("resolution",resolution);
    shader.setUniformTexture("tex0",image0.getTexture(),0);
}


