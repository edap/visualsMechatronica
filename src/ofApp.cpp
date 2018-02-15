#include "ofApp.h"
#include "Scenes.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    init_context();
    SM.addScene<Scene0>(42);

    finalFbo.allocate(1280, 720, GL_RGBA);
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

    setupAudio();

    finalFbo.begin();
    ofClear(255,255,255, 0);
    finalFbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofxGlobalContext::Manager::defaultManager().update();

    finalFbo.begin();
    tex0.bind();
    rayMarching.begin();
    setUniforms();
    plane.draw();
    rayMarching.end();
    tex0.unbind();
    finalFbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    finalFbo.draw(0,0);
}

void ofApp::setUniforms(){
    float resolution[] = {float(ofGetWidth()), float(ofGetHeight())};
    float time = ofGetElapsedTimef();
    rayMarching.setUniform1f("iGlobalTime",time);
    rayMarching.setUniform2fv("resolution",resolution);
    rayMarching.setUniformTexture("tex0",image0.getTexture(),0);
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    if (audioDisabled) { return; };
    for (int i = 0; i < bufferSize; i++){
        wave = sample.play();
        //fft
        if(fft.process(wave)){
            fft.magsToDB();
        }
        mymix.stereo(wave, outputs, 0.5);
        output[i*nChannels    ] = outputs[0];
        output[i*nChannels + 1] = outputs[1];
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

void ofApp::setupAudio(){
    if (audioDisabled) { return; };
    sample.load(ofToDataPath("music/I-Am-Mensch.wav"));

    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512;

    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    // the higher the value, the more accurate will be the fft analysis
    fftSize = 1024;
    fft.setup(fftSize, 512, 256);
    /* this has to happen at the end of setup - it switches on the DAC */
    // TODO, Change with stream options
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    //ofSetBackgroundColor(255, 200, 0);
}

void ofApp::init_context(){
    ofxGlobalContext::Manager::defaultManager().createContext<AppTime>();
}
