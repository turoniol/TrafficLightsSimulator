#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H
#include <QGraphicsItem>
#include "map/map.h"

#define RED 32
#define GREEN 64
#define YELLOW 128

class TrafficLight : public QGraphicsPixmapItem
{
private:
    Map *map_ptr;
    std::vector<Block*> container;
    unsigned int color;
    bool refered;
    bool in_group;
public:
    TrafficLight();
    TrafficLight(Map &ptr);
    void searchCrossroad();
    void setTrafficLight(std::vector<TrafficLight *> &light_ptr);
    void setFullBlock();
    void checkColor();
    void setGroup(bool value);
    void setColorRed();
    void setColorGreen();
    void setColorYellow();
    // getters
    TrafficLight *getTrafficLightVector();
    unsigned int getContainerSize() const;
    bool isInGroup() const;
    void setPtr(Map &ptr);
};

#endif // TRAFFICLIGHT_H
