#include "ofApp.h"
#include "Scenes.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    setupAudio();

    //Scenes
    init_context();
    $Context(Panel)->setup();
    SM.addScene<Scene0>();
    SM.addScene<Scene1>();
    SM.addScene<Scene2>();
    SM.addScene<DebugFFT>();
    SM.changeScene("Scene0");

    //FBO
    finalFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
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
        currentSample = sample.play();
        if (fft.process(currentSample)) {
            oct.calculate(fft.magnitudes);
        }
        mix.stereo(currentSample, outputs, 0.5);
        buffer[i*buffer.getNumChannels()] = outputs[0];
        buffer[i*buffer.getNumChannels()+1] = outputs[1];
    }
    cout << oct.averages[0]<< endl;
    cout << oct.averages[17]<< endl;
}


void ofApp::switchBand(int key){
    if(key == 3814) $Context(AudioAnalysis)->changeBand(1);
    if(key == 3812) $Context(AudioAnalysis)->changeBand(-1);
}

void ofApp::switchScene(int key){

    if(key == 'q') SM.changeScene<Scene0>(0.1);
    if(key == 'w') SM.changeScene<Scene1>(0.1);
    if(key == 'e') SM.changeScene<Scene2>(0.1);
    if(key == 'o') SM.changeScene<DebugFFT>(0.1);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << key << endl;
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

    //fft.setup(fftSize, 512, 256);
    //oct.setup(sampleRate, 1024, 2);
    fft.setup(1024, 512, 256);
    //oct.setup(44100, 1024, 10);
    oct.setup(44100, 1024, 2);
    //oct.setup(sampleRate, 1024, 10);
    // setting the averages of samples to count to 2 instead of 10
    //make the selection of the octaves more simpler
    sample.load(ofToDataPath("music/I-Am-Mensch.wav"));
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 4);
}

void ofApp::init_context(){
    ofxGlobalContext::Manager::defaultManager().createContext<AppTime>();
    ofxGlobalContext::Manager::defaultManager().createContext<Panel>();
    ofxGlobalContext::Manager::defaultManager().createContext<AudioAnalysis>(oct);
}
