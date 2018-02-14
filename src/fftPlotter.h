#pragma once
#include "ofMain.h"
#include "ofxMaxim.h"

class fftPlotter{
public:
    static void draw(const ofxMaxiFFT& fft, const int& fftSize, const int& selectedBin);
};
