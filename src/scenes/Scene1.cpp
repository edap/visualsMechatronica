#include "Scene1.h"

Scene1::Scene1() {
    LM.setup(ofGetWidth(), ofGetHeight());
    LM.createLayer<RayMarchRings>(0.3);
}

void Scene1::update(){
    LM.update();
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene1::draw(){
     LM.draw();
}

void Scene1::viewWillAppear() {
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene1::viewDidAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene1::viewWillDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene1::viewDidDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}
