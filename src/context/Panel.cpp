#include "Panel.h"

Panel::Panel(){}

void Panel::setup(){
    gui.setup();
    gui.setPosition(glm::vec2(0,20));
    gui.add(audioSmooth.setup("audioSmooth", 0.5, 0.2, 2.0));
    gui.add(audioMag.setup("audioMag", 0.05, 0.0, 1.2));

    gui.add(sdf1.setup("sdfSize1", 0.5, 0.0, 1.0));
    gui.add(sdf2.setup("sdfSize2", 0.5, 0.0, 1.0));
    gui.add(sdfOp.setup("sdf Op", 11, 0, 18));
    gui.add(sdfOpRadius.setup("sdfOpRadius", 0.7, 0.6, 2.0));
    gui.add(sdfOpStairs.setup("sdfOpStairs", 4, 0, 40));
    gui.add(sdfSolidId1.setup("sdfSolidId1", 2, 0, 19));
    gui.add(sdfSolidId2.setup("sdfSolidId2", 5, 0, 19));
    gui.add(sdfSolid2Pos.setup("sdfSolid2Pos", glm::vec3(0.,0.,0.), glm::vec3(0.,0.,0.), glm::vec3(2.,2.,2.)));
    gui.add(sdfModelId.setup("sdfModelId", 4, 0, 10));
}

void Panel::draw(){
    ofDrawBitmapString(ofGetFrameRate(),0,10, 0);
    gui.draw();
}
