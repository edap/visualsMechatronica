#include "MercurySketch.h"

MercurySketch::MercurySketch() {
    cout << "MercurySketch: " << endl;
    LM1.setup(ofGetWidth(), ofGetHeight());
    LM1.createLayer<MercuryModels>(0.3);
}

void MercurySketch::update(){
    LM1.update();
    //cout << __PRETTY_FUNCTION__ << endl;
}

void MercurySketch::draw(){
     LM1.draw();
}

void MercurySketch::viewWillAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void MercurySketch::viewDidAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void MercurySketch::viewWillDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void MercurySketch::viewDidDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}
