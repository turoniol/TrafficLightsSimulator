#include "layer.h"
#include "QDebug"

Layer::Layer(const unsigned int n_neurons, const unsigned int n_inputs)
{
    std::string fname("neuron");
    number_of_inputs = n_inputs;
    number_of_neurons = n_neurons;
    neurons = new Neuron[number_of_neurons];
    for(unsigned int i = 0; i < number_of_neurons; ++i){
        fname = "neuron" + std::to_string(i) + ".txt";
        neurons[i].create(n_inputs, &fname);
    }
}

void Layer::mutate(){
    for(unsigned int i = 0; i < number_of_neurons; ++i)
        neurons[i].mutate();
}

Layer* Layer::copy(){
    auto obj = new Layer(number_of_neurons, number_of_inputs);
    for(unsigned int i = 0; i < number_of_neurons; ++i)
        obj->neurons[i] = *neurons[i].copy();
    return obj;
}

void Layer::calculate(float *input, float *output)
{
    for(unsigned int i = 0; i < number_of_neurons; ++i)
        output[i] = neurons[i].calculate(input);
}

unsigned int Layer::getNoN() const
{
    return number_of_neurons;
}
