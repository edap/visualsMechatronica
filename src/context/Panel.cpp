#include "Panel.h"

Panel::Panel(){}

void Panel::setup(){
    gui.setup();
    gui.setPosition(glm::vec2(0,20));
    gui.add(audioSmooth.setup("audioSmooth", 0.5, 0., 2.0));
    gui.add(audioMag.setup("audioMag", 0.05, 0.0, 0.2));
}

void Panel::draw(){
    ofDrawBitmapString(ofGetFrameRate(),0,10, 0);
    gui.draw();
}
