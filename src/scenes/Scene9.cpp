#include "Scene9.h"

Scene9::Scene9() {
    LM.setup(ofGetWidth(), ofGetHeight());
    LM.createLayer<Multistructure>(0.3);
}

void Scene9::update(){
    LM.update();
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene9::draw(){
     LM.draw();
}

void Scene9::viewWillAppear() {
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene9::viewDidAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene9::viewWillDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene9::viewDidDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}
