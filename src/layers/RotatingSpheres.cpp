#include "RotatingSpheres.h"

void RotatingSpheres::loadAssets(){
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/two_spheres.frag", "");
    image0.load("textures/BlueFrontedParrot.jpg");
}

void RotatingSpheres::setUniforms(){
    float resolution[] = {float(ofGetWidth()), float(ofGetHeight())};
    float time = ofGetElapsedTimef();

    //$Context(AppTime)->elapsed * 0.8;

    shader.setUniform1f("iGlobalTime",time);
    shader.setUniform2fv("resolution",resolution);
    shader.setUniformTexture("tex0",image0.getTexture(),0);

    setOctaves();
}

void RotatingSpheres::setOctaves(){
    auto oct = $Context(AudioAnalysis)->getOct();

    auto octAvgs = oct.averages;
    auto octNavgs = oct.nAverages;

    shader.setUniform1f("oct1",(1 + octAvgs[1]*10));

//    for (int i = 0; i<octNavgs; i++) {
//        ofColor col;
//        col.setHsb((int)ofMap(i, 0, octNavgs, 0, 255), 255, 255);
//        ofSetColor(col);

//        float size = 1 + octAvgs[i]*10;
//        int x = (int) (ofGetWidth()/2) * i/octNavgs + ofGetWidth()/4;

//        ofDrawRectangle(x, ofGetHeight()/1.2, 10, -size);
//        ofDrawBitmapString(i, x, ofGetHeight()/1.15);
//    }
}
