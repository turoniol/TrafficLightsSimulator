#include "net.h"
#include "QDebug"
Net::Net(const unsigned int n_neurons, const unsigned int n_inputs){
    inlayer = new Layer(n_neurons, n_inputs);
}

float Net::calculate(float *input)
{
    float* outarray = new float[inlayer->getNoN()];
    inlayer->calculate(input, outarray);
    float first = 0, second = 0;
    for(unsigned int i = 0; i < inlayer->getNoN(); ++i){
        if(i % 2 == 0){
            first += outarray[i];
        }
        else{
            second += outarray[i];
        }
    }
    return first - second;
}

void Net::mutate(){
    inlayer->mutate();
}
