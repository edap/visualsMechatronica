#include "AudioAnalysis.h"

AudioAnalysis::AudioAnalysis(const maxiFFTOctaveAnalyzer& _oct){
    oct = _oct;

    for(auto nBands : nFilteredBands){
        std::deque<float> deq {0.,11};
        mappedBands.insert(make_pair(nBands, deq));
    }
}

maxiFFTOctaveAnalyzer AudioAnalysis::getOct() const {
    return oct;
}

void AudioAnalysis::changeBand(int val){
    if(val > 0){
        selectedBand == (oct.nAverages-1) ? selectedBand = 0 : selectedBand += 1;
    }

    if(val < 0){
        selectedBand == 0 ? selectedBand = (oct.nAverages-1) : selectedBand -= 1;
    }
};

int AudioAnalysis::getBand(){
    return selectedBand;
};


float AudioAnalysis::getFilteredBand(int n_band, float smoothValue){
    auto octAvgs = oct.averages;
    auto o =  octAvgs[n_band];
    if (!mappedBands.count(n_band)){
        //ofLogError("band "+ ofToString(n_band) + "not in vector nFilteredBands, add it if you need it");
        return rectBoxcarFilter(o, &tmpHistory, smoothValue);
    } else {
       return rectBoxcarFilter(o, &mappedBands[n_band], smoothValue);
    }
};

// this is a low band filter. I'm not sure how accurate it is, but it works for my needs.
// references:
//
// https://terpconnect.umd.edu/~toh/spectrum/Smoothing.html
// http://www.analog.com/media/en/technical-documentation/dsp-book/dsp_book_Ch15.pdf

// It accepts two parameters, val is the value to be smoothed, _history is a deque
// that contains the last 11 values. If there are no 11 values in the queue, it will fullfill and in
// the meantime it will return 0
float AudioAnalysis::rectBoxcarFilter(const float val, std::deque<float>* _history, float smoothValue){

    // guard, sometimes the octave analysis return negative values
    // for the bin at the end of the spektrum
    if (isnan(val)) { return 0; }

    if (_history->size() >= max_history) {
        _history->pop_front();
        _history->push_back(val);

        float sum = 0;
        float shape = -5; // values goes from -5 to +5, the curve described by this values
        // define the shape of the filter. It could also have been from 0 to 10
        for (int i = 0; i< max_history; i++) {
            sum += _history->at(i) * (coef + shape);
            shape+=1;
        }

        sum /= max_history;
        coef = (sum/coef ) * smoothValue;
        return coef;
    } else {
       _history->push_back(val);
       return 0.0;
    }
};
