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
    SM.addScene<MercurySketch>();
    SM.changeScene("Scene0");

    finalFbo.allocate( ofGetWidth(),ofGetHeight(), GL_RGBA);
    finalFbo.begin();
    ofClear(255,255,255, 0);
    finalFbo.end();

    //setup video and audio recording();
    recorder.setup(sampleRate, 60, 2);
    ofEnableAlphaBlending();
}

void ofApp::update(){

    ofxGlobalContext::Manager::defaultManager().update();
    SM.update();

    finalFbo.begin();
    //ofClear(0, 0, 0, 1);
    ofClear(255, 255, 255, 0); // 0 is important. this is for transparent BG.
    SM.draw();
    finalFbo.end();

    recorder.recVideo(finalFbo);
}

void ofApp::draw(){
    ofSetColor(255);
    finalFbo.draw(0, 0);

    if (drawGui) $Context(Panel)->draw();
}

void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    if (audioDisabled) { return; };
    if (ofGetElapsedTimef() < 5.00){ return; };

    for (unsigned i = 0 ; i< bufferSize; i++) {
        currentSample = sample.play();
        if (fft.process(currentSample)) {
            oct.calculate(fft.magnitudes);
        }
        mix.stereo(currentSample, outputs, 0.5);
        output[i*nChannels] = outputs[0];
        output[i*nChannels+1] = outputs[1];
    }

    recorder.recAudio(output, bufferSize, nChannels);
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
    if(key == 'p') SM.changeScene<MercurySketch>(0.1);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switchScene(key);
    switchBand(key);

    if(key == 'g') drawGui = !drawGui;

    if(key == 'm'){
        auto filename = ofToString(ofGetElapsedTimef())+".png";
        img.grabScreen(0,0,ofGetWidth(), ofGetHeight());

        ofPixels pix;
        finalFbo.readToPixels(pix);
        ofSaveImage(pix, filename, OF_IMAGE_QUALITY_BEST);
        //img.save(filename, OF_IMAGE_QUALITY_BEST);
    }
}

void ofApp::setupAudio(){
    if (audioDisabled) { return; };

    fft.setup(1024, 512, 256);
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
