#include "Scene10.h"

Scene10::Scene10() {
    LM.setup(ofGetWidth(), ofGetHeight());
    LM.createLayer<Mensch>(0.3);
}

void Scene10::update(){
    LM.update();
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene10::draw(){
     LM.draw();
}

void Scene10::viewWillAppear() {
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene10::viewDidAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene10::viewWillDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene10::viewDidDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}
