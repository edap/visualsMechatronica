#include "Panel.h"

Panel::Panel(){}

void Panel::setup(){
    gui.setup();
    gui.setPosition(glm::vec2(0,20));
    gui.add(audioSmooth.setup("audioSmooth", 0.5, 0., 2.0));
    gui.add(audioMag.setup("audioMag", 0.05, 0.0, 0.2));

    gui.add(sdf1.setup("sdfSize1", 0.5, 0.0, 1.0));
    gui.add(sdf2.setup("sdfSize2", 0.5, 0.0, 1.0));
    gui.add(sdfOp.setup("sdf Op", 5, 0, 18));
    gui.add(sdfSolidId1.setup("sdfSolidId1", 0, 0, 19));
    gui.add(sdfSolidId2.setup("sdfSolidId2", 0, 0, 19));
    gui.add(sdfSolid2Pos.setup("sdfSolid2Pos", glm::vec3(1.,1.,1.), glm::vec3(-2.,-2.,-2.), glm::vec3(2.,2.,2.)));
}

void Panel::draw(){
    ofDrawBitmapString(ofGetFrameRate(),0,10, 0);
    gui.draw();
}
