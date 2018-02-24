#include "Scene6.h"

Scene6::Scene6() {
    LM.setup(ofGetWidth(), ofGetHeight());
    LM.createLayer<Multistructure>(0.3);
}

void Scene6::update(){
    LM.update();
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene6::draw(){
     LM.draw();
}

void Scene6::viewWillAppear() {
    //cout << __PRETTY_FUNCTION__ << endl;
}

void Scene6::viewDidAppear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene6::viewWillDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}

void Scene6::viewDidDisappear() {
    cout << __PRETTY_FUNCTION__ << endl;
}
