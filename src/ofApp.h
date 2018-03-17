#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxAnimationPrimitives.h"
#include "ofxVideoRecorder.h"
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
    void exit();

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
    void audioOut(ofSoundBuffer &buffer);
    void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args);

private:
    void init_context();
    // Methods
    void setupAudio();
    void switchScene(int key);
    void switchBand(int key);

    // Video recording
    void setupVideoRecording();
    void videoRecEvent(int key);
    void recVideo();

    ofxVideoRecorder vidRecorder;
    string fileName;
    string fileExt;
    bool bRecording;
    ofPixels pixels; // this is used to store the pixels read from the fbo

    // Animation Primitives
    ofxAnimationPrimitives::SceneManager SM;

    // Audio vars
    bool          audioDisabled = false;
    unsigned startTime, endTime, currentTime;
    unsigned sampleRate = 44100;
    unsigned bufferSize = 512;
    double frequency, currentSample;
    double outputs[2];

    maxiMix mix;
    ofxMaxiSample sample;

    maxiFFT fft;
    maxiFFTOctaveAnalyzer oct;
    // end audio

    //graphics vars
    ofFbo                 finalFbo;
    bool                  drawGui = true;
    //end graphics
};
