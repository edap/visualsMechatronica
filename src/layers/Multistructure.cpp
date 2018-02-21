#include "Multistructure.h"

void Multistructure::loadAssets(){
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/mercury_structure.frag", "");
    image0.load("textures/eastern-rosella-big.jpg");
    image1.load("textures/1.jpg");
    image2.load("textures/3.jpg");
    image3.load("textures/4.jpg");
    image4.load("textures/5.jpg");
    image5.load("textures/6.jpg");
    image6.load("textures/9a.jpg");
}

void Multistructure::setUniforms(){
    float resolution[] = { float(ofGetWidth()), float(ofGetHeight()) };
    float time = ofGetElapsedTimef();
    int n_band = $Context(AudioAnalysis)->getBand();
    float beat = $Context(AudioAnalysis)->smoothBand(n_band) * $Context(Panel)->audioMag;

    float sdf1 = $Context(Panel)->sdf1;
    float sdf2 = $Context(Panel)->sdf2;
    int sdfOp = $Context(Panel)->sdfOp;
    int sdfSolidId1 = $Context(Panel)->sdfSolidId1;
    int sdfSolidId2 = $Context(Panel)->sdfSolidId2;
    glm::vec3 solid2Pos = $Context(Panel)->sdfSolid2Pos;
    //float b = $Context(AudioAnalysis)->smoothBand(6) * $Context(Panel)->audioMag;
    //cout << b << endl;

    shader.setUniform1f("iGlobalTime", time);
    shader.setUniform1f("beat", beat);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform1f("sdf1", sdf1);
    shader.setUniform1f("sdf2", sdf2);
    shader.setUniform1i("sdfOp", sdfOp);
    shader.setUniform1i("sdfSolidId1", sdfSolidId1);
    shader.setUniform1i("sdfSolidId2", sdfSolidId2);
    shader.setUniform3f("solid2Pos", solid2Pos);
    shader.setUniformTexture("tex0", image0.getTexture(), 0);
    shader.setUniformTexture("tex1", image1.getTexture(), 1);
    shader.setUniformTexture("tex2", image2.getTexture(), 2);
    shader.setUniformTexture("tex3", image3.getTexture(), 3);
    shader.setUniformTexture("tex4", image4.getTexture(), 4);
    shader.setUniformTexture("tex5", image5.getTexture(), 5);
    shader.setUniformTexture("tex6", image6.getTexture(), 6);
}
