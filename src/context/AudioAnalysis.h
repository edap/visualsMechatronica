#pragma once
#include "ofxGlobalContext.h"
#include "ofxMaxim.h"

class AudioAnalysis : public ofxGlobalContext::Context{
public:
    AudioAnalysis(const ofxMaxiFFT& _fft, const int& _fftSize);
    virtual ~AudioAnalysis() {}
    void update();

private:
    ofxMaxiFFT fft;
    int fftSize;
};
