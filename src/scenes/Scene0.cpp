#include "Scene0.h"

Scene0::Scene0(const int arg0) {
    cout << "Scene0: " << arg0 << endl;
    LM.setup(ofGetWidth(), ofGetHeight());
    LM.createLayer<RayMarchRings>(0.3);
}

void Scene0::update(){
    LM.update();
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene0::draw(){
     LM.draw();
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
