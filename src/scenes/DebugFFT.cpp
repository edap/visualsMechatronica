#include "DebugFFT.h"

DebugFFT::DebugFFT() {
    cout << "DebugFFT: " << endl;
    LM1.setup(ofGetWidth(), ofGetHeight());
    LM1.createLayer<PlotOctave>(0.3);
}

void DebugFFT::update(){
    LM1.update();
    cout << __PRETTY_FUNCTION__ << endl;
}

void DebugFFT::draw(){
     LM1.draw();
}

void DebugFFT::viewWillAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void DebugFFT::viewDidAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void DebugFFT::viewWillDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void DebugFFT::viewDidDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}
