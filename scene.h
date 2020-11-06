#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>
#include <map.h>
#include <carcenter.h>
#include <tlcontrol.h>

class Scene : public QGraphicsScene
{
private:
    bool system_on = false;
    Map map;
    CarCenter car_centers;
    std::vector<TrafficLightGroup*> traffic_lights_group;
    std::vector <TLControl*> controlers;
public:
    void addMap(const QString &file_name);
    void addTrafficLights();
    void addCar();
    void renewTLStatus();
    ~Scene();
    unsigned int getCarNumber() const;
    void setSystem_on(bool value);
    bool getSystem_on() const;
};

#endif // SCENE_H
