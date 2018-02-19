#pragma once
#include "ofxGlobalContext.h"
#include "ofxMaxim.h"

class AudioAnalysis : public ofxGlobalContext::Context{
public:
    AudioAnalysis(const maxiFFTOctaveAnalyzer& _oct);
    virtual ~AudioAnalysis() {}
    maxiFFTOctaveAnalyzer getOct() const;
    void changeBand(int n_band);
    int getBand();
    float getBandAvgs();

    float smoother = 0.5;
    float smoothedVolume = 80;
    float scaledVolume = 0;
    vector <float> volHistory;

    std::deque<float> history;

private:
    int selectedBand = 0;
    maxiFFTOctaveAnalyzer oct;

    float smoothBand(const float oct);
};
