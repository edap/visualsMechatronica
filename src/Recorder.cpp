#include "Recorder.h"

Recorder::Recorder(){
    fileName = "testMovie";
    // ffmpeg uses the extension to determine the container type. run 'ffmpeg -formats' to see supported formats
    fileExt = ".mov";
    // see available codecs in ffmpeg with 'ffmpeg -codecs'. In my experience, h264 leads to better results
    vidRecorder.setVideoCodec("h264");
    //vidRecorder.setVideoBitrate("30000k"); // try 20M to have high res, but slower performances
    vidRecorder.setVideoBitrate("50M"); // 50mb works just with certain shaders
}

void Recorder::setup(int _sampleRate, int _fps, int _nChannels){
    sampleRate = _sampleRate;
    fps = _fps;
    nChannels = _nChannels;

    ofAddListener(vidRecorder.outputFileCompleteEvent, this, &Recorder::recordingComplete);
    ofAddListener(ofEvents().exit, this, &Recorder::exit);
    ofAddListener(ofEvents().keyPressed, this, &Recorder::videoRecEvent);

    bRecording = false;
}

void Recorder::videoRecEvent(ofKeyEventArgs& args){
    ofLog() << args.key;
    if (args.key == 43) {
        bRecording = !bRecording;
        if (bRecording && !vidRecorder.isInitialized()) {
            //vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, ofGetWidth(), ofGetHeight(), 60); // no audio
            vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, ofGetWidth(), ofGetHeight(), fps, sampleRate, nChannels);
            vidRecorder.start();
        }
        else if (!bRecording && vidRecorder.isInitialized()) {
            vidRecorder.setPaused(true);
        }
        else if (bRecording && vidRecorder.isInitialized()) {
            vidRecorder.setPaused(false);
        }
    }
    if (args.key==45) {
        bRecording = false;
        vidRecorder.close();
    }
}

void Recorder::recVideo(const ofFbo& finalFbo){
    if (bRecording) {
        ofPixels pixels;
        finalFbo.readToPixels(pixels);
        bool success = vidRecorder.addFrame(pixels);
        if (!success) {
            ofLogWarning("This frame was not added!");
        }
    }

    // Check if the video recorder encountered any error while writing video frame or audio smaples.
    if (vidRecorder.hasVideoError()) {
        ofLogWarning("The video recorder failed to write some frames!");
    }

    if (vidRecorder.hasAudioError()) {
        ofLogWarning("The video recorder failed to write some audio samples!");
    }
}

void Recorder::recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args){
    cout << "The recoded video file is now complete." << endl;
}


void Recorder::recAudio(float * output, int bufferSize, int nChannels){
    if (bRecording) {
       vidRecorder.addAudioSamples(output, bufferSize, nChannels);
    }
}

void Recorder::exit(ofEventArgs& args){
    ofRemoveListener(vidRecorder.outputFileCompleteEvent, this, &Recorder::recordingComplete);
    ofRemoveListener(ofEvents().exit, this, &Recorder::exit);
    ofRemoveListener(ofEvents().keyPressed, this, &Recorder::videoRecEvent);

    vidRecorder.close();
}
