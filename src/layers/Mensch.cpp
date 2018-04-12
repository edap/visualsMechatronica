#include "Mensch.h"

void Mensch::loadAssets(){
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/blobby.frag", "");
    image0.load("textures/eastern-rosella/eastern-rosella.jpg");
    image1.load("textures/fischers-lovebird/fischers-lovebird3.jpg");
    image2.load("textures/budgeridgar/5.jpg");
    image3.load("textures/fischers-lovebird/fischers-lovebird-big.jpg");
    image4.load("textures/budgeridgar/5a2.jpg");
    image5.load("textures/eastern-rosella/eastern-rosella-det2.jpg");
    image6.load("textures/9a.jpg");
}

void Mensch::setUniforms(){
    float resolution[] = { float(ofGetScreenWidth()), float(ofGetScreenHeight()) };
    float time = ofGetElapsedTimef();
    int n_band = $Context(AudioAnalysis)->getBand();
    float beat = $Context(AudioAnalysis)->getFilteredBand(n_band) * $Context(Panel)->audioMag;
    if (beat < 0) {
        beat = 0.00;
    }
    //float b = $Context(AudioAnalysis)->smoothBand(6) * $Context(Panel)->audioMag;
    //cout << beat << endl;

    shader.setUniform1f("iGlobalTime", time);
    shader.setUniform1f("beat", beat);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniformTexture("tex0", image0.getTexture(), 0);
    shader.setUniformTexture("tex1", image1.getTexture(), 1);
    shader.setUniformTexture("tex2", image2.getTexture(), 2);
    shader.setUniformTexture("tex3", image3.getTexture(), 3);
    shader.setUniformTexture("tex4", image4.getTexture(), 4);
    shader.setUniformTexture("tex5", image5.getTexture(), 5);
    shader.setUniformTexture("tex6", image6.getTexture(), 6);
}
