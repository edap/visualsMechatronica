#include "ofApp.h"
#include "Scenes.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    // Audio, play the track and initialize audio analysis
    setupAudio();

    // Contexts. This is where the state is saved
    init_context();
    $Context(Panel)->setup();

    //Scenes
    SM.addScene<Scene0>();
    SM.addScene<Scene1>();
    SM.addScene<Scene2>();
    SM.addScene<Scene3>();
    SM.addScene<Scene4>();
    SM.addScene<Scene5>();
    SM.addScene<Scene6>();
    SM.addScene<Scene7>();
    SM.addScene<Scene8>();
    SM.addScene<Scene9>();
    SM.addScene<Scene10>();
    SM.addScene<DebugFFT>();
    SM.changeScene("Scene0");

    finalFbo.allocate( ofGetWidth(),ofGetHeight(), GL_RGBA);
    finalFbo.begin();
    ofClear(0, 0, 0, 0);
    finalFbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofxGlobalContext::Manager::defaultManager().update();
    SM.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // fullfill the FBO
    finalFbo.begin();
    ofClear(0, 0, 0, 255);

    SM.draw();
    finalFbo.end();

    // draw the FBO
    ofSetColor(255);
    finalFbo.draw(0, 0);

    if (drawGui) $Context(Panel)->draw();
}


void ofApp::audioOut(ofSoundBuffer &buffer){
    if (audioDisabled) { return; };
    for (unsigned i = 0 ; i< bufferSize; i++) {
        //currentSample = (env.adsr(osc.sinewave(frequency + mod.sinewave(1)*440),env.trigger))/2;
        currentSample = sample.play();
        if (fft.process(currentSample)) {
            oct.calculate(fft.magnitudes);
        }
        mix.stereo(currentSample, outputs, 0.5);
        buffer[i*buffer.getNumChannels()] = outputs[0];
        buffer[i*buffer.getNumChannels()+1] = outputs[1];
    }
}


void ofApp::switchBand(int key){
    if(key == 3814) $Context(AudioAnalysis)->changeBand(1);
    if(key == 3812) $Context(AudioAnalysis)->changeBand(-1);
}

void ofApp::switchScene(int key){

    if(key == 'q') SM.changeScene<Scene0>(0.1);
    if(key == 'w') SM.changeScene<Scene1>(0.1);
    if(key == 'e') SM.changeScene<Scene2>(0.1);
    if(key == 'r') SM.changeScene<Scene3>(0.1);
    if(key == 't') SM.changeScene<Scene4>(0.1);

    if(key == 'a') SM.changeScene<Scene5>(0.1);
    if(key == 's') SM.changeScene<Scene6>(0.1);
    if(key == 'd') SM.changeScene<Scene7>(0.1);
    if(key == 'f') SM.changeScene<Scene8>(0.1);
    if(key == 'z') SM.changeScene<Scene9>(0.1);
    if(key == 'x') SM.changeScene<Scene10>(0.1);

    if(key == 'o') SM.changeScene<DebugFFT>(0.1);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switchScene(key);
    switchBand(key);
    if(key == 'g') drawGui = !drawGui;
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

    sampleRate = 44100;
    bufferSize = 512;

    fft.setup(1024, 512, 256);
    //oct.setup(44100, 1024, 10);
    oct.setup(44100, 1024, 2); // meno esempi, piu' facile da analizzare

    sample.load(ofToDataPath("music/I-Am-Mensch.wav"));
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 4);

    startTime = ofGetElapsedTimeMillis();
    endTime = 1000;
}

void ofApp::init_context(){
    ofxGlobalContext::Manager::defaultManager().createContext<AppTime>();
    ofxGlobalContext::Manager::defaultManager().createContext<Panel>();
    ofxGlobalContext::Manager::defaultManager().createContext<AudioAnalysis>(oct);
}
