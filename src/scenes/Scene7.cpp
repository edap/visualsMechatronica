#include "Scene7.h"

Scene7::Scene7() {
    LM.setup(ofGetWidth(), ofGetHeight());
    LM.createLayer<Multistructure>(0.3);
}

void Scene7::update(){
    LM.update();
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene7::draw(){
     LM.draw();
}

void Scene7::viewWillAppear() {
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene7::viewDidAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene7::viewWillDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene7::viewDidDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}
