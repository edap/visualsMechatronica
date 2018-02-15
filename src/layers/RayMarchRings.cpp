#include "RayMarchRings.h"

void RayMarchRings::setup(){
    fbo.allocate(1280, 720, GL_RGBA);
    ofDisableArbTex();
    plane.setResolution(2,2);
    plane.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    plane.set(ofGetWidth(), ofGetHeight());
    light.enable();
    image0.load("textures/eastern-rosella-big.jpg");
    tex0 = image0.getTexture();

#ifdef TARGET_OPENGLES
    shader.load("shadersES2/shader");
#else
    if(ofIsGLProgrammableRenderer()){
        rayMarching.load("shaders_gl3/passthruogh.vert", "shaders_gl3/march1.frag", "");
    }else{
        rayMarching.load("shaders_gl3/passthruogh.vert", "shaders_gl3/march1.frag", "");
    }
#endif

    //clean the FBO
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
}

void RayMarchRings::update(){
    fbo.begin();
    tex0.bind();
    rayMarching.begin();
    setUniforms();
    plane.draw();
    rayMarching.end();
    tex0.unbind();
    fbo.end();
}

void RayMarchRings::draw(){
    fbo.draw(0,0);
}

void RayMarchRings::setUniforms(){
    float resolution[] = {float(ofGetWidth()), float(ofGetHeight())};
    float time = ofGetElapsedTimef();
    rayMarching.setUniform1f("iGlobalTime",time);
    rayMarching.setUniform2fv("resolution",resolution);
    rayMarching.setUniformTexture("tex0",image0.getTexture(),0);
}
