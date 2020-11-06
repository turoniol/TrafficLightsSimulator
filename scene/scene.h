#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>
#include "map/map.h"
#include "cars/carcenter.h"
#include "traffic_light/tlcontrol.h"

class Scene : public QGraphicsScene
{
  Q_OBJECT
private:
    bool system_on = false;
    Map map;
    CarCenter car_centers;
    QTimer *carSpawnTimer;
    QTimer *trafficLightsTimer;
    std::vector <TrafficLightGroup*> traffic_lights_group;
    std::vector <TLControl*> controlers;
public:
    Scene();
    void addMap(const QString &file_name);
    void addTrafficLights();
    void addCar();
    void renewTLStatus();
    void setSystem_on(bool value);
    bool getSystem_on() const;
    ~Scene();
};

#endif // SCENE_H
