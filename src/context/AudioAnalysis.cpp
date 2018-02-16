#include "AudioAnalysis.h"

AudioAnalysis::AudioAnalysis(const ofxMaxiFFT& _fft, const int& _fftSize, const maxiFFTOctaveAnalyzer& _oct){
    fft = _fft;
    fftSize = _fftSize;
    oct = _oct;
}

void AudioAnalysis::update(){
// test to see if it was working
//    for(int i = 0; i < fftSize ;i++){
//        cout << fft.magnitudesDB[i] << endl;
//    }
}

int AudioAnalysis::getFFTSize()const {
    return fftSize;
}

ofxMaxiFFT AudioAnalysis:: getFFT() const {
    return fft;
}

maxiFFTOctaveAnalyzer AudioAnalysis::getOct() const {
    return oct;
}


