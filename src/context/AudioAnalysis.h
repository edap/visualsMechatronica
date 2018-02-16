#pragma once
#include "ofxGlobalContext.h"
#include "ofxMaxim.h"

class AudioAnalysis : public ofxGlobalContext::Context{
public:
    AudioAnalysis(const ofxMaxiFFT& _fft, const int& _fftSize, const maxiFFTOctaveAnalyzer& _oct);
    virtual ~AudioAnalysis() {}
    void update();

    int getFFTSize() const;
    ofxMaxiFFT getFFT() const;
    maxiFFTOctaveAnalyzer getOct() const;

private:
    ofxMaxiFFT fft;
    int fftSize;
    maxiFFTOctaveAnalyzer oct;
};
