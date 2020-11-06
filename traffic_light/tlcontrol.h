#ifndef TLCONTROL_H
#define TLCONTROL_H
#include "neural_net/net.h"
#include "trafficlightgroup.h"

class TLControl
{
private:
    float result;
    Net* net;
    TrafficLightGroup* group;
public:
    TLControl(TrafficLightGroup &tlg);
    void createNet();
    void calculate();
    void mutate();
    void setStatus();
};

#endif // TLCONTROL_H
