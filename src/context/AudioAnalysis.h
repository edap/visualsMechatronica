#pragma once
#include "ofxGlobalContext.h"
#include "ofxMaxim.h"
#include "Panel.h"

class AudioAnalysis : public ofxGlobalContext::Context{
public:
    AudioAnalysis(const maxiFFTOctaveAnalyzer& _oct);
    virtual ~AudioAnalysis() {}
    maxiFFTOctaveAnalyzer getOct() const;
    void changeBand(int n_band);
    int getBand();
    float smoothBand(int n_band);


private:
    maxiFFTOctaveAnalyzer oct;

    // Filtering
    // There are two kind of queue where to save the values to filter. The tmpHistory
    // and the mappedBands hsitory. In the first one, the que is fullfilled
    // for the given band and an average is calculated.
    // The second one stores the values of multiple bands. This is useful when you need to
    // read the values of multiple band in a single scene. for example
    // you want to have a circle that moves according to the bass
    // and a square that moves according to the high pitch sounds
    std::deque<float> tmpHistory;
    map<int, std::deque<float>> mappedBands;

    vector<int> nFilteredBands = {1,6,7,8,9};
    int selectedBand = 0;

    // Rectangular Boxcar Filter
    // This is the number of values the will be stored in the hisotry
    int max_history = 11; //choose always a odd number.
    float coef = 80;
    float rectBoxcarFilter(const float oct, std::deque<float>* _history);
};
