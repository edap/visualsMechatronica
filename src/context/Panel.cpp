#include "Panel.h"

Panel::Panel(){}

void Panel::setup(){
    gui.setup();
    gui.add(displacement.setup("displacement", 0, 0.5, 1.0));
}

void Panel::drawGui(){
    gui.draw();
}
