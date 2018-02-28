#include "Scene3.h"

Scene3::Scene3() {
    LM.setup(ofGetWidth(), ofGetHeight());
    LM.createLayer<Deformed1>(0.3);
}

void Scene3::update(){
    LM.update();
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene3::draw(){
     LM.draw();
}

void Scene3::viewWillAppear() {
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene3::viewDidAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene3::viewWillDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene3::viewDidDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}
