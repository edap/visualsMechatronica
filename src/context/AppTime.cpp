#include "AppTime.h"

AppTime::AppTime(){
    elapsed = 0;
    rate = 0;
}

void AppTime::update(){
    float inv_target_frame = (1. / 60);
    tick = ofGetLastFrameTime();
    rate = tick / inv_target_frame;
    elapsed += tick;
}
