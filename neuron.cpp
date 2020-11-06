#include "neuron.h"
#include "math.h"
#include "cstdlib"
#include "ctime"
#include "QString"
#include "QDir"
//        weights[i] = std::rand() % 10000 / 10000.0f - 0.5f;
Neuron::Neuron(const unsigned int n, std::string *filename)
{
    srand(time(nullptr));
    create(n, filename);
}
Neuron::Neuron(){
    srand(time(nullptr));
    create(0, nullptr);
}
void Neuron::mutate()
{
    for(unsigned int i = 0; i < number_of_inputs; ++i)
        weights[i] += rand_shift - 2.0f*(std::rand() % 10000 / 10000.0f)*rand_shift;
    shift += rand_shift - 2.0f*(std::rand() % 10000 / 10000.0f)*rand_shift;
}

Neuron* Neuron::copy(){
    Neuron* obj = new Neuron(number_of_inputs, nullptr);
    obj->shift = shift;
    for(unsigned int i = 0; i < number_of_inputs; ++i)
        obj->weights[i] = weights[i];
    return obj;
}

void Neuron::create(const unsigned n, std::string* filename)
{
    if(filename != nullptr){
        std::ifstream file;
        std::ofstream fout;
        fout.open("fout.txt");
        file.open( "./neurons_weights/" + *filename);
        number_of_inputs = n;
        shift = 0.0f;
        weights = new float[n];
        for(unsigned int i = 0; i < number_of_inputs; ++i){
            file >> weights[i];
            fout << weights[i] << " ";
        }
        file.close();
    }
}

float Neuron::calculate(float* input)
{
    float s = shift;
    for(unsigned int i = 0; i < number_of_inputs; ++i)
        s += weights[i]*input[i];
    s = 1.0f/(1 + expf(-s));
    return s;
}
