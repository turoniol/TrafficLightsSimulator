#ifndef CARCENTER_H
#define CARCENTER_H
#include <block.h>
#include <car.h>
#include <QGraphicsItem>

class CarCenter : public QGraphicsRectItem
{
private:
    Car* car;
    std::vector<Block*> spawners;
    unsigned int car_number, car_iterations;
public:
    CarCenter();
    void searchCenterPoint(Map *map);
    Car &addNewCar(Map *map_ptr);
    unsigned int getCarNumber() const;
};
#endif // CARCENTER_H
