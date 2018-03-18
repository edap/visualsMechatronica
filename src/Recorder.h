#pragma once
#include "ofMain.h"
#include "ofxVideoRecorder.h"

class Recorder{
public:
    Recorder();

    // Video recording
    void setup(int sampleRate, int fps, int nChannels);
    void recVideo(const ofFbo& finalFbo);
    void recAudio(float * output, int bufferSize, int nChannels);
    //events
    void exit(ofEventArgs& args);
    void videoRecEvent(ofKeyEventArgs& key);
    void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args);

    int sampleRate;
    int fps;
    int nChannels;

    ofxVideoRecorder vidRecorder;
    string fileName;
    string fileExt;
    bool bRecording;
};
