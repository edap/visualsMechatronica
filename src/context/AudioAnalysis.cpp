#include "AudioAnalysis.h"

AudioAnalysis::AudioAnalysis(const maxiFFTOctaveAnalyzer& _oct){
    oct = _oct;
}

maxiFFTOctaveAnalyzer AudioAnalysis::getOct() const {
    return oct;
}


