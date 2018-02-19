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
    //cout << octAvgs[0]<< endl;
    //cout << octAvgs[17]<< endl;
    smoothBand(o);
    return o;
};

float AudioAnalysis::smoothBand(const float oct){
    int max_history = 5;//choose always a odd number
    // guard, sometimes the octave analysis return negative values
    // for the bin at the end of the spektrum
    // cout << oct << endl;

    if (history.size() >= max_history) {

        history.pop_front();
        history.push_back(oct);

        float sum = 0;
        float shape = -2;
        for(int i = 0; i< max_history; i++){
            sum += history[i] * (smoothedVolume + shape);
            shape+=1;
        }

        sum /= max_history;




        smoothedVolume += 0.07 * (sum/smoothedVolume);
        return sum;
    }else{
       history.push_back(oct);
       return 0.0;
    }
};
