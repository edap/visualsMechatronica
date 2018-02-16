#pragma once
#include "ofxGlobalContext.h"
#include "ofxMaxim.h"

class AudioAnalysis : public ofxGlobalContext::Context{
public:
    AudioAnalysis(const maxiFFTOctaveAnalyzer& _oct);
    virtual ~AudioAnalysis() {}
    maxiFFTOctaveAnalyzer getOct() const;

private:
    maxiFFTOctaveAnalyzer oct;
};
