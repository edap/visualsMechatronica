#include "fftPlotter.h"

void fftPlotter::draw(const ofxMaxiFFT& fft, const int& fftSize, const int& selectedBin){
    float width = float(ofGetWidth()) / float(fftSize) /2.f;
    for(int i = 0; i < fftSize ;i++){
        int r = float(255) / float(fftSize) * i;
        int g = 40;
        int b = 255 - r;
        ofSetColor(r, g, b);
        ofDrawCircle(ofGetWidth()/2 +width * i,
                     ofGetHeight()/2, fft.magnitudes[i] * 2);

        ofDrawCircle(ofGetWidth()/2 -width * i,
                     ofGetHeight()/2, fft.magnitudes[i] * 2);
        ofDrawRectangle(i * 2, ofGetHeight(), 2, -(fft.magnitudesDB[i]) * 8);
    }
}
