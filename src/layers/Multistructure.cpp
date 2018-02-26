#include "Multistructure.h"

void Multistructure::loadAssets(){
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/multistructure.frag", "");
    image4.load("textures/fischers-lovebird/fischers-lovebird3.jpg");
}

void Multistructure::setUniforms(){
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

    float sdf1, sdf2, sdfOpRadius, sdfOpStairs;
    int sdfOp, sdfSolidId1, sdfSolidId2;
    glm::vec3 solid2Pos;

    sdfOp = 11;
    sdfSolidId1 = 2;
    sdfSolidId2 =5;
    solid2Pos = glm::vec3(0.,0.,0.);
    sdf1 = 1.0;
    sdf2 = 0.335 * (0.1 + max(0.0, beat));
    sdfOpRadius = 0.854;
    sdfOpStairs = 4.;

    shader.setUniform1f("iGlobalTime", time);
    shader.setUniform1f("beat", beat);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform1f("sdf1", sdf1);
    shader.setUniform1f("sdf2", sdf2);
    shader.setUniform1i("sdfOp", sdfOp);
    shader.setUniform1f("sdfOpRadius", sdfOpRadius);
    shader.setUniform1f("sdfOpStairs", sdfOpStairs);
    shader.setUniform1i("sdfSolidId1", sdfSolidId1);
    shader.setUniform1i("sdfSolidId2", sdfSolidId2);
    shader.setUniform3f("solid2Pos", solid2Pos);
    shader.setUniformTexture("tex4", image4.getTexture(), 4);

}

float Multistructure::max(float min, float max){
    return max > min ? max : min;
};
