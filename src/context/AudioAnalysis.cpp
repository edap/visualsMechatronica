#include "AudioAnalysis.h"

AudioAnalysis::AudioAnalysis(const ofxMaxiFFT& _fft, const int& _fftSize){
    fft = _fft;
    fftSize = _fftSize;
}

void AudioAnalysis::update(){
    for(int i = 0; i < fftSize ;i++){
//        int r = float(255) / float(fftSize) * i;
//        int g = 40;
//        int b = 255 - r;
//        ofSetColor(r, g, b);
//        ofDrawCircle(ofGetWidth()/2 +width * i,
//                     ofGetHeight()/2, fft.magnitudes[i] * 2);

//        ofDrawCircle(ofGetWidth()/2 -width * i,
//                     ofGetHeight()/2, fft.magnitudes[i] * 2);
//        ofDrawRectangle(i * 2, ofGetHeight(), 2, -(fft.magnitudesDB[i]) * 8);

        cout << fft.magnitudesDB[i] << endl;
    }
}


