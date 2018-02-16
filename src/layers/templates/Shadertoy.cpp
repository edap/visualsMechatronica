#include "Shadertoy.h"

void Shadertoy::setup(){
    ofDisableArbTex();
    plane.setResolution(2,2);
    plane.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    plane.set(ofGetWidth(), ofGetHeight());
    image0.load("textures/eastern-rosella-big.jpg");
    tex0 = image0.getTexture();

#ifdef TARGET_OPENGLES
    rayMarching.load("shadersES2/shader");
#else
    if(ofIsGLProgrammableRenderer()){
        shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/march1.frag", "");
    }else{
        shader.load("shaders_gl3/passthruogh.vert", "shaders_gl3/march1.frag", "");
    }
#endif

}

void Shadertoy::draw(){
    shader.begin();
    setUniforms();
    plane.draw();
    shader.end();
}

void Shadertoy::setUniforms(){
    float resolution[] = {float(ofGetWidth()), float(ofGetHeight())};
    float time = ofGetElapsedTimef();

    //$Context(AppTime)->elapsed * 0.8;

    shader.setUniform1f("iGlobalTime",time);
    shader.setUniform2fv("resolution",resolution);
    shader.setUniformTexture("tex0",image0.getTexture(),0);
}
