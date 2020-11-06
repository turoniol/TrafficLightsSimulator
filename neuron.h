#ifndef NEURON_H
#define NEURON_H
#include <vector>
#include <fstream>

class Neuron
{
private:
    float* weights;
    static constexpr float rand_shift = 0.1f;
    unsigned int number_of_inputs;
    float shift;
public:
    Neuron(const unsigned int n, std::string *filename);
    Neuron();
    void mutate();
    float calculate(float* input);
    Neuron *copy();
    void create(const unsigned n, std::string *filename);
};

#endif // NEURON_H
