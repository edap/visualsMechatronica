#include "Scene2.h"

Scene2::Scene2() {
    LM.setup(ofGetWidth(), ofGetHeight());
    LM.createLayer<Multistructure>(0.3);
}

void Scene2::update(){
    LM.update();
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene2::draw(){
     LM.draw();
}

void Scene2::viewWillAppear() {
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene2::viewDidAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene2::viewWillDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene2::viewDidDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}
