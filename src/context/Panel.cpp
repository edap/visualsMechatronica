#include "Panel.h"

Panel::Panel(){}

void Panel::setup(){
    gui.setup();
    gui.setPosition(glm::vec2(0,20));
    gui.add(displacement.setup("displacement", 0, 0.5, 1.0));
}

void Panel::draw(){
    ofDrawBitmapString(ofGetFrameRate(),0,10, 0);
    gui.draw();
}
