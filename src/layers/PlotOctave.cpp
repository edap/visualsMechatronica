#include "PlotOctave.h"
#include "ofMain.h"

void PlotOctave::draw(){
    auto oct = $Context(AudioAnalysis)->getOct();

    auto octAvgs = oct.averages;
    auto octNavgs = oct.nAverages;

    for (int i = 0; i<octNavgs; i++) {
        ofColor col;
        col.setHsb((int)ofMap(i, 0, octNavgs, 0, 255), 255, 255);
        ofSetColor(col);

        float size = 1 + octAvgs[i]*10;
        int x = (int) (ofGetWidth()/2) * i/octNavgs + ofGetWidth()/4;

        ofDrawRectangle(x, ofGetHeight()/1.2, 10, -size);
        ofDrawBitmapString(i, x, ofGetHeight()/1.15);
    }
}
