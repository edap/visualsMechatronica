#include "ofApp.h"
#include "Scenes.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    setupAudio();

    //Scenes
    init_context();
    SM.addScene<Scene0>(42);
    SM.addScene<DebugFFT>();
    SM.changeScene("Scene0");

    //FBO
    finalFbo.allocate(1280, 720, GL_RGBA);
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
}


//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    if (audioDisabled) { return; };
    for (int i = 0; i < bufferSize; i++){
        wave = sample.play();
        //fft
        if(fft.process(wave)){
            oct.calculate(fft.magnitudes);
        }
        mymix.stereo(wave, outputs, 0.5);
        output[i*nChannels    ] = outputs[0];
        output[i*nChannels + 1] = outputs[1];
    }
}

void ofApp::switchScene(int key){
    if(key == 'q') SM.changeScene<Scene0>(0.1);
    if(key == 'o') SM.changeScene<DebugFFT>(0.1);
    //if(key == 2) SM.changeScene<Flying>(0.1);
    //if(key == 3) SM.changeScene<Scene3>(0.1);
    //if(key == 4) SM.changeScene<Scene4>(0.1);
    //if(key == 5) SM.changeScene<Scene5>(0.1);
    //if(key == 6) SM.changeScene<Theta>(0.1);
    //if (key == 7) SM.changeScene<Universe>(0.1);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << key << endl;
    switchScene(key);
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

    oct.setup(sampleRate, 1024, 2); // setting the averages of samples to count to 2 make the selection
    // of the octaves more simpler

    //oct.setup(sampleRate, 1024, 10);
    /* this has to happen at the end of setup - it switches on the DAC */
    // TODO, Change with stream options
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    //ofSetBackgroundColor(255, 200, 0);
}

void ofApp::init_context(){
    ofxGlobalContext::Manager::defaultManager().createContext<AppTime>();
    ofxGlobalContext::Manager::defaultManager().createContext<AudioAnalysis>(fft, fftSize, oct);
}
