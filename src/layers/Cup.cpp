        #include "Cup.h"

    void Cup::loadAssets(){
        shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/cup.frag", "");
        image0.load("textures/budgeridgar/5.jpg");
    }

    void Cup::setUniforms(){
        int nBand = 6;

        // debug with panel
        float audioMag = $Context(Panel)->audioMag;
        float smoothVal = $Context(Panel)->audioSmooth;
        //float audioMag = 0.0425;
        //float smoothVal = 2.936;
        // int nBand = $Context(AudioAnalysis)->getBand();
        float resolution[] = { float(ofGetWidth()), float(ofGetHeight()) };
        float time = ofGetElapsedTimef();

        float beat = $Context(AudioAnalysis)->getFilteredBand(nBand, smoothVal) * audioMag;

        shader.setUniform1f("iGlobalTime", time);
        shader.setUniform1f("beat", beat);
        shader.setUniform2fv("resolution", resolution);
        shader.setUniformTexture("tex0", image0.getTexture(), 0);
    }

