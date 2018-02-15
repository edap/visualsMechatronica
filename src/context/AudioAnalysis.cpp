#include "AudioAnalysis.h"

AudioAnalysis::AudioAnalysis()
{

}

void AudioAnalysis::setup(){

}

void AudioAnalysis::audioOut(float * output, int bufferSize, int nChannels){
    if (audioDisabled) { return; };
    for (int i = 0; i < bufferSize; i++){
        wave = sample.play();
        //fft
        if(fft.process(wave)){
            fft.magsToDB();
        }
        mymix.stereo(wave, outputs, 0.5);
        output[i*nChannels    ] = outputs[0];
        output[i*nChannels + 1] = outputs[1];
    }
}
