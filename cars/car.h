#ifndef CAR_H
#define CAR_H
#include <QGraphicsItem>
#include <QTimer>
#include "map/map.h"
#include <fstream>

class Car : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QPixmap pixmap;
    Map* map_ptr;
    Block* previous_block;
    QPointF position;

    unsigned int direction, random;
    int speed_x, speed_y;
    unsigned int size_x, size_y;
    bool isReversed;
public:
    Car(QPointF start_pos, Map *map_ptr);
   ~Car();
    void setSpeed();
    void setDirection();
    void choosePixmapDirection();
    void chooseCarColor(int prmtr);
    void rotate();
    bool isNextBlockFull();
    bool isNextBlock();
    Block &getNextBlock();
    bool canDeleteCar();
public slots:
    void move();
};

#endif // CAR_H
