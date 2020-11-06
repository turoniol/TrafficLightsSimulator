#ifndef NET_H
#define NET_H
#include <layer.h>

class Net
{
private:
    Layer* inlayer;
public:
    float calculate(float* input);
    Net(const unsigned int n_neurons, const unsigned int n_inputs);
    void mutate();
};

#endif // NET_H
