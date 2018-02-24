#include "Scene3.h"

Scene8::Scene8() {
    LM.setup(ofGetWidth(), ofGetHeight());
    LM.createLayer<Multistructure>(0.3);
}

void Scene8::update(){
    LM.update();
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene8::draw(){
     LM.draw();
}

void Scene8::viewWillAppear() {
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene8::viewDidAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene8::viewWillDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene8::viewDidDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}
