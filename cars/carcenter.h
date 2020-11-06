#ifndef CARCENTER_H
#define CARCENTER_H
#include "map/block.h"
#include "car.h"
#include <QGraphicsItem>
#include <QTimer>

class CarCenter : public QObject, public QGraphicsRectItem
{
  Q_OBJECT
private:
    QTimer* carMoveTimer;
    QVector<Block*> spawners;
    QVector<Car*> cars;
    Car *findNullPtr();
public:
    CarCenter();
    void searchCenterPoint(Map *map);
    Car &addNewCar(Map *map_ptr);
    ~CarCenter();
};
#endif // CARCENTER_H
