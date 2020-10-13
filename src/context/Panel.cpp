#include "Panel.h"

Panel::Panel(){}

void Panel::setup(){
    gui.setup();

    gui.setPosition(glm::vec2(0,20));
    gui.add(u_camx.setup("u_camx", 0.9, -5.0, 5.0));
    gui.add(u_camy.setup("u_camy", 0.5, -5.0, 5.0));
    gui.add(u_fov.setup("u_fov", 9.0, 0.0, 15.0));
    gui.add(u_texId.setup("u_texId", 0, 0, 6));
    gui.add(audioSmooth.setup("audioSmooth", 0.5, 0.2, 8.0));
    gui.add(audioMag.setup("audioMag", 0.05, 0.0, 0.5));
    gui.add(time.setup("time", 0.0, 0.0, 400.0));
    gui.add(sdf1.setup("sdfSize1", 0.5, 0.0, 1.0));
    gui.add(sdf2.setup("sdfSize2", 0.5, 0.0, 1.0));
    gui.add(sdfOp.setup("sdf Op", 11, 0, 18));
    gui.add(sdfOpRadius.setup("sdfOpRadius", 0.7, 0.6, 2.0));
    gui.add(sdfOpStairs.setup("sdfOpStairs", 4, 0, 40));
    gui.add(sdfSolidId1.setup("sdfSolidId1", 2, 0, 19));
    gui.add(sdfSolidId2.setup("sdfSolidId2", 5, 0, 19));
    gui.add(sdfSolid2Pos.setup("sdfSolid2Pos", glm::vec3(0.,0.,0.), glm::vec3(0.,0.,0.), glm::vec3(2.,2.,2.)));
    gui.add(sdfModelId.setup("sdfModelId", 4, 0, 17));
    gui.add(color.set("color", ofColor(0), ofColor(0), ofColor(255)));
    gui.loadFromFile("settings.xml");
}

void Panel::draw(){
    ofDrawBitmapString(ofGetFrameRate(),0,10, 0);
    gui.draw();
}
