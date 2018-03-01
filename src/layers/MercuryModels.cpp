#include "MercuryModels.h"

void MercuryModels::loadAssets(){
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/mercury_models.frag", "");
    image0.load("textures/eastern-rosella/eastern-rosella.jpg");
    image1.load("textures/eastern-rosella/eastern-rosella-det.jpg");
    image2.load("textures/budgeridgar/5.jpg");
    image3.load("textures/budgeridgar/5a.jpg");
    image4.load("textures/fischers-lovebird/fischers-lovebird3.jpg");
    image5.load("textures/fischers-lovebird/fischers-lovebird-big.jpg");
    image6.load("textures/9a.jpg");
}

void MercuryModels::setUniforms(){
    float resolution[] = { float(ofGetWidth()), float(ofGetHeight()) };
    float time = ofGetElapsedTimef();
    int nBand = $Context(AudioAnalysis)->getBand();
    float audioMag = $Context(Panel)->audioMag;
    float smoothVal = $Context(Panel)->audioSmooth;
    //float audioMag = 0.024;
    //float smoothVal = 1.27;
    //int nBand = 1;

    float beat = $Context(AudioAnalysis)->getFilteredBand(nBand, smoothVal) * audioMag;
    int model = $Context(Panel)->sdfModelId;

    float sdf1, sdf2, sdfOpRadius, sdfOpStairs;
    int sdfOp, sdfSolidId1, sdfSolidId2;
    glm::vec3 solid2Pos;
    cout << model << endl;
    cout << "model" << endl;
    if (model == 0){
        sdfOp = 11;
        sdfSolidId1 = 2;
        sdfSolidId2 =5;
        solid2Pos = glm::vec3(0.,0.,0.);

        sdf1 = 0.345;
        sdf2 = 0.555;
        //sdfOpRadius = 0.6 * beat;
        sdfOpRadius = 0.6;
        sdfOpStairs = 7.6;
    }else if (model == 1){
        sdfOp = 11;
        sdfSolidId1 = 2;
        sdfSolidId2 =5;
        solid2Pos = glm::vec3(0.,0.,0.);

        sdf1 = 0.345;
        sdf2 = 0.555;
        //sdfOpRadius = 0.6 * beat;
        sdfOpRadius = 0.6;
        sdfOpStairs = 7.6;
    }else if(model == 2){
        sdfOp = 11;
        sdfSolidId1 = 2;
        sdfSolidId2 =5;
        solid2Pos = glm::vec3(0.,0.,0.);

        sdf1 = 1.;
        //sdf2 = 0.695 * beat;
        sdf2 = 0.695;
        sdfOpRadius = 0.932;
        sdfOpStairs = 1.2;
    } else if(model == 3){
            sdfOp = 11;
            sdfSolidId1 = 2;
            sdfSolidId2 =5;
            solid2Pos = glm::vec3(0.,0.,0.);
            sdf1 = 1.0;
            sdf2 = 0.335 * (0.1 + max(0.0, beat));
            sdfOpRadius = 0.854;
            sdfOpStairs = 4.;
    } else if(model == 4){
            sdfOp = 11;
            sdfSolidId1 = 2;
            sdfSolidId2 =5;
            solid2Pos = glm::vec3(0.,0.,0.);

            sdf1 = 0.;
            //sdf2 = 0.79 * beat;
            sdf2 = 0.79;
            sdfOpRadius = 1.274;
            sdfOpStairs = 3.6;
    } else if(model == 5){
            sdfOp = 8;
            sdfSolidId1 = 2;
            sdfSolidId2 = 19;
            solid2Pos = glm::vec3(0.,0.,0.);

            sdf1 = 0.515;
            //sdf2 = 0.74 - beat;
            sdf2 = 0.74;
            sdfOpRadius = 0.8;
            sdfOpStairs = 4.;
    } else if(model == 6){
            sdfOp = 8;
            sdfSolidId1 = 2;
            sdfSolidId2 = 5;
            solid2Pos = glm::vec3(0.,0.,0.);

            sdf1 = 0.345;
            //sdf2 = 0.48 -  beat;
            sdf2 = 0.48;
            sdfOpRadius = 0.8;
            sdfOpStairs = 4.;
    } else if(model == 7){
            sdfOp = 5;
            sdfSolidId1 = 2;
            sdfSolidId2 =5;
            solid2Pos = glm::vec3(0.,0.,0.);

            sdf1 = 0.05;
            //sdf2 = 0.88 - beat;
            sdf2 = 0.88;
            sdfOpRadius = 0.8;
            sdfOpStairs = 4.;
    } else if(model == 8){
            sdfOp = 5;
            sdfSolidId1 = 2;
            sdfSolidId2 =6;
            solid2Pos = glm::vec3(0.,0.,0.);

            sdf1 = 0.505;
            sdf2 = 0.735;
            //sdfOpRadius = 1.0 - beat * 0.6; //0.8. it goes from 0.6 to 1.1
            sdfOpRadius = 0.8;
            sdfOpStairs = 4.;
    } else if(model == 9){
            sdfOp = 5;
            sdfSolidId1 = 2;
            sdfSolidId2 = 15;
            solid2Pos = glm::vec3(0.,0.,0.);

            sdf1 = 0.505;
            //sdf2 = 0.835 - beat;
            sdf2 = 0.835;
            sdfOpRadius = 0.8;
            sdfOpStairs = 4.;
    } else if(model == 10){
            sdfOp = 5;
            sdfSolidId1 = 2;
            sdfSolidId2 = 17;
            solid2Pos = glm::vec3(0.,0.,0.);

            sdf1 = 0.9;
            //sdf2 = 0.825 + ( beat * 0.075); //0.825
            sdf2 = 0.825;
            sdfOpRadius = 0.8;
            sdfOpStairs = 4.;
    }

    else{
        sdf1 = $Context(Panel)->sdf1;
        sdf2 = $Context(Panel)->sdf2;
        sdfOp = $Context(Panel)->sdfOp;
        sdfSolidId1 = $Context(Panel)->sdfSolidId1;
        sdfSolidId2 = $Context(Panel)->sdfSolidId2;
        solid2Pos = $Context(Panel)->sdfSolid2Pos;
        //float b = $Context(AudioAnalysis)->smoothBand(6) * $Context(Panel)->audioMag;
        //cout << b << endl;
        sdfOpRadius = $Context(Panel)->sdfOpRadius;
        sdfOpStairs = $Context(Panel)->sdfOpStairs;
    }


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
    shader.setUniformTexture("tex0", image0.getTexture(), 0);
    shader.setUniformTexture("tex1", image1.getTexture(), 1);
    shader.setUniformTexture("tex2", image2.getTexture(), 2);
    shader.setUniformTexture("tex3", image3.getTexture(), 3);
    shader.setUniformTexture("tex4", image4.getTexture(), 4);
    shader.setUniformTexture("tex5", image5.getTexture(), 5);
    shader.setUniformTexture("tex6", image6.getTexture(), 6);
}

float MercuryModels::max(float min, float max){
    return max > min ? max : min;
};
