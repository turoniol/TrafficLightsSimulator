#ifndef LAYER_H
#define LAYER_H
#include <neuron.h>

class Layer
{
private:
    unsigned int number_of_neurons, number_of_inputs;
    Neuron* neurons;
public:
    Layer(const unsigned int n_neurons, const unsigned int n_inputs);
    void mutate();
    Layer *copy();
    void calculate(float *input, float *output);
    unsigned int getNoN() const;
};

#endif // LAYER_H
