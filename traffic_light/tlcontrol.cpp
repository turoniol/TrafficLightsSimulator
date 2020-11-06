#include "tlcontrol.h"

TLControl::TLControl(TrafficLightGroup &tlg)
{
    group = &tlg;
}

void TLControl::createNet()
{
    net = new Net(group->getLineNumber(), group->getZoneBlockNumber());
}

void TLControl::mutate(){
    net->mutate();
}

void TLControl::calculate(){
    float* inarray = new float[group->getZoneBlockNumber()];
    for (unsigned int i = 0; i < group->getZoneBlockNumber(); ++i){
        inarray[i] = group->getBlockFullAt(i);
    }
    result = net->calculate(inarray);
}

void TLControl::setStatus(){
    if(result > 0)
        group->setStatus(0);
    else if(result < 0)
        group->setStatus(1);

    group->renewTLStatus();
    group->changeStatus();
}
