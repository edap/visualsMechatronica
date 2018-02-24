#include "Scene5.h"

Scene5::Scene5() {
    LM.setup(ofGetWidth(), ofGetHeight());
    LM.createLayer<Multistructure>(0.3);
}

void Scene5::update(){
    LM.update();
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene5::draw(){
     LM.draw();
}

void Scene5::viewWillAppear() {
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene5::viewDidAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene5::viewWillDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene5::viewDidDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}
