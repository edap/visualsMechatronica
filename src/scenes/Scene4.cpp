#include "Scene4.h"

Scene4::Scene4() {
    LM.setup(ofGetWidth(), ofGetHeight());
    LM.createLayer<Multistructure>(0.3);
}

void Scene4::update(){
    LM.update();
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene4::draw(){
     LM.draw();
}

void Scene4::viewWillAppear() {
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene4::viewDidAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene4::viewWillDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene4:viewDidDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}
