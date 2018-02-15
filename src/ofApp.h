#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "fftPlotter.h"
#include "ofxAutoReloadedShader.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    // Methods
    void setUniforms();
    void audioOut(float * output, int bufferSize, int nChannels);
    void setupAudio();

    // Audio vars
    bool          audioDisabled = false;
    int		      bufferSize;
    int           sampleRate;
    int           fftSize;
    ofxMaxiSample sample;
    maxiMix       mymix;
    double        wave;
    double        outputs[2];
    ofxMaxiFFT    fft;
    // end audio

    //graphics vars
    ofLight               light;
    ofxAutoReloadedShader rayMarching;
    ofImage               image0;
    ofTexture             tex0;
    ofPlanePrimitive      plane;
    ofFbo                 fbo;
    //end graphics
};
