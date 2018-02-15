#pragma once
#include "ofMain.h"
#include "ofxGlobalContext.h"
#include "ofxMaxim.h"

class AudioAnalysis : public ofxGlobalContext::Context{
public:
    AudioAnalysis();
    virtual ~AudioAnalysis() {}

    void setup();
    void update(float * output, int bufferSize, int nChannels);
    void draw();
    void audioOut(float * output, int bufferSize, int nChannels);
    void setupAudio();

private:
    // Audio vars
    bool          audioDisabled = false;
    int		      bufferSize = 0;
    int           sampleRate = 0;
    int           fftSize = 0;
    ofxMaxiSample sample;
    maxiMix       mymix;
    double        wave = 0.00;
    double        outputs[2];
    ofxMaxiFFT    fft;
    // end audio
};
