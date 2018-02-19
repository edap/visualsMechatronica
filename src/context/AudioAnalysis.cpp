#include "AudioAnalysis.h"

AudioAnalysis::AudioAnalysis(const maxiFFTOctaveAnalyzer& _oct){
    oct = _oct;
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

float AudioAnalysis::getBandAvgs(){
    auto octAvgs = oct.averages;
    auto o =  octAvgs[selectedBand];
    return smoothBand(o);
};

float AudioAnalysis::smoothBand(const float oct){
    int max_history = 11;//choose always a odd number
    // guard, sometimes the octave analysis return negative values
    // for the bin at the end of the spektrum
    if (isnan(oct)) { return 0; }

    if (history.size() >= max_history) {
        history.pop_front();
        history.push_back(oct);

        float sum = 0;
        float shape = -5;
        for(int i = 0; i< max_history; i++){
            sum += history[i] * (coef + shape);
            shape+=1;
        }

        sum /= max_history;
        coef = sum/coef;
        return coef;
    }else{
       history.push_back(oct);
       return 0.0;
    }
};
