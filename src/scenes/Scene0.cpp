#include "Scene0.h"

Scene0::Scene0(const int arg0) {
    cout << "Scene0: " << arg0 << endl;
}


void Scene0::update(){
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene0::draw(){
    ofSetColor(100, 0, 0, 255 * getAlpha());
    ofRect(0, 0, ofGetWidth() / 2, ofGetHeight());


    ofSetColor(255);
    ofDrawBitmapString("SCENE0 alpha:" + ofToString(getAlpha(), 3), 10, 20);
}

void Scene0::viewWillAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene0::viewDidAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene0::viewWillDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene0::viewDidDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}
