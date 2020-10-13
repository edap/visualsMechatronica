#include "RayMarchRings.h"

void RayMarchRings::loadAssets(){
    shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/raymarching/blending_rings.frag", "");
//    image0.load("textures/fischers-lovebird/fischers-lovebird-big.jpg");
//    image1.load("textures/eastern-rosella/eastern-rosella-det.jpg");
//    image2.load("textures/budgeridgar/5.jpg");
//    image3.load("textures/budgeridgar/5a.jpg");
//    image4.load("textures/fischers-lovebird/fischers-lovebird3.jpg");
//    image5.load("textures/eastern-rosella/eastern-rosella.jpg");
//    image6.load("textures/9a.jpg");

    image0.load("textures/punta-g-soldaten-ara2.jpg");

    //image1.load("textures/punta-g-soldaten-ara.jpg");
    image1.load("textures/punta-alaintera.jpg");
    image2.load("textures/argusianus-argus2.jpg");

//    image3.load("textures/punta-scarlet-macaw3.jpg");
//    image4.load("textures/punta-soldaten-ara.jpg");
//    image5.load("textures/punta-soldaten-ara2.jpg");
//    image6.load("textures/punta-rubrogenis.jpg");

    image6.load("textures/ocellate-turkey-tex.jpg");
    image5.load("textures/pink-necked-green-pigeon-big.jpg");
    image4.load("textures/sonnenralle-full.png");
    image3.load("textures/sunbittern3.jpg");

}

void RayMarchRings::setUniforms(){
    float resolution[] = { float(ofGetWidth()), float(ofGetHeight()) };
    float time = ofGetElapsedTimef();
    if($Context(Panel)->time < $Context(Panel)->time.getMax()) {
        time = $Context(Panel)->time;
    }
    auto bgCol = $Context(Panel)->color.get();

    //$Context(AppTime)->elapsed * 0.8;

    shader.setUniform1f("iGlobalTime",time);
    shader.setUniform2fv("resolution",resolution);
    shader.setUniform4f("bgCol", bgCol);
    //shader.setUniform3fv("bgColor", );
    shader.setUniformTexture("tex0",image0.getTexture(),0);

    shader.setUniformTexture("tex1", image1.getTexture(), 1);
    shader.setUniformTexture("tex2", image2.getTexture(), 2);
    shader.setUniformTexture("tex3", image3.getTexture(), 3);
    shader.setUniformTexture("tex4", image4.getTexture(), 4);
    shader.setUniformTexture("tex5", image5.getTexture(), 5);
    shader.setUniformTexture("tex6", image6.getTexture(), 6);


    shader.setUniform1f("u_camx", $Context(Panel)->u_camx);
    shader.setUniform1f("u_camy", $Context(Panel)->u_camy);
    shader.setUniform1f("u_fov", $Context(Panel)->u_fov);
    shader.setUniform1f("u_fov", $Context(Panel)->u_fov);
    shader.setUniform1i("u_texId", $Context(Panel)->u_texId);

}


