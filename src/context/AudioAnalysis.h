#pragma once
#include "ofxGlobalContext.h"
#include "ofxMaxim.h"
#include "Panel.h"

class AudioAnalysis : public ofxGlobalContext::Context{
public:
    AudioAnalysis(const maxiFFTOctaveAnalyzer& _oct);
    virtual ~AudioAnalysis() {}
    void update();
    maxiFFTOctaveAnalyzer getOct() const;
    void changeBand(int n_band);
    int getBand();
    float smoothBand(int n_band);

    // This is the number of values that it will averaged
    int max_history = 11;//choose always a odd number.
    float coef = 80;


    // use this if you want to read the values of only one band for each scene
    std::deque<float> history;

    // use this if you want to read multiple bands values for each scene, for example
    // you want to have a cirve that move according to the bass
    // and a square for the high pitch sounds
    vector<int> nFilteredBands = {2,6,7,8,9};
    // this is used to find the index in the historyBands
    map<int, std::deque<float>> mappedBands;
    vector<std::deque<float>> historyBands;

private:
    int selectedBand = 0;
    maxiFFTOctaveAnalyzer oct;
    float rectBoxcarFilter(const float oct, std::deque<float>* _history);
    float updateFilteredBands();
};
