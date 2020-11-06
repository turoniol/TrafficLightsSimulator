#ifndef TRAFFICLIGHTGROUP_H
#define TRAFFICLIGHTGROUP_H
#include "trafficlight.h"
#include <QTimer>

class TrafficLightGroup : public QObject{
    Q_OBJECT
private:
    QTimer *timer;
    Map* map_ptr;
    std::vector <TrafficLight*> group;
    std::vector <Block*> zone;
    unsigned int zone_size;
    int time;
    bool status, prevstatus;

    void addZoneLeft(int x, int y);
    void addZoneRight(int x, int y);
    void addZoneUp(int x, int y);
    void addZoneDown(int x, int y);

private slots:
    void changeColor();
public:
    TrafficLightGroup(Map *map_ptr);
    void joinTL(TrafficLight *tl, TrafficLight *array[]);
    void changeStatus();
    void setZone();
    void include(const unsigned int x_pos, const unsigned int y_pos, TrafficLight *array[]);
    unsigned int getLineNumber() const;
    unsigned int getZoneBlockNumber() const;
    bool getBlockFullAt(unsigned int iterator);
    void setStatus(bool value);
    void renewTLStatus();
    ~TrafficLightGroup();
};

#endif // TRAFFICLIGHTGROUP_H
