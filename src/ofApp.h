#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxAnimationPrimitives.h"
//Context
#include "ofxGlobalContext.h"
#include "context/AppTime.h"
#include "context/AudioAnalysis.h"
#include "context/Panel.h"

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
    void init_context();
    // Methods
    void audioOut(float * output, int bufferSize, int nChannels);
    void setupAudio();
    void switchScene(int key);

    // Animation Primitives
    ofxAnimationPrimitives::SceneManager SM;

    // Audio vars
    bool          audioDisabled = false;
    int		      bufferSize = 512;
    int           sampleRate = 44100;
    int           fftSize = 1024;
    ofxMaxiSample sample;
    maxiMix       mymix;
    double        wave;
    double        outputs[2];
    ofxMaxiFFT    fft;
    maxiFFTOctaveAnalyzer oct;
    // end audio

    //graphics vars
    ofFbo                 finalFbo;
    bool                  drawGui;
    //end graphics
};
