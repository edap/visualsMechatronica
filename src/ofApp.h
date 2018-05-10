#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxAnimationPrimitives.h"
#include "ofxVideoRecorder.h"
//Context
#include "ofxGlobalContext.h"
#include "context/AppTime.h"
#include "context/AudioAnalysis.h"
#include "context/Panel.h"
//Video and Audio Recorder
#include "Recorder.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void audioOut(float * output, int bufferSize, int nChannels);

private:
    void init_context();
    // Methods
    void setupAudio();
    void switchScene(int key);
    void switchBand(int key);

    // Video recording
    Recorder recorder;

    // Animation Primitives
    ofxAnimationPrimitives::SceneManager SM;

    // Audio vars
    bool audioDisabled = false;
    unsigned startTime, endTime, currentTime;
    int sampleRate = 44100;
    unsigned bufferSize = 512;
    double frequency, currentSample;
    double outputs[2];

    maxiMix mix;
    ofxMaxiSample sample;

    maxiFFT fft;
    maxiFFTOctaveAnalyzer oct;
    // end audio

    //graphics vars
    ofFbo                 finalFbo;
    bool                  drawGui = false;

    ofImage img;
};
